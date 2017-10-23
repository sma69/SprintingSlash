#include "gf2d_collision.h"
/*
int checkWallCollision(Entity * self, Entity * other)
{
	//The sides of the Entity Hitboxes
	//The sides of the rectangles
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	//Calculate the sides of the main entity
	leftA = self->body.x;
	rightA = self->body.x + self->body.w;
	topA = self->body.y;
	bottomA = self->body.y + self->body.h;

	//Calculate the sides of the other entity
	leftB = other->body.x;
	rightB = other->body.x + other->body.w;
	topB = other->body.y;
	bottomB = other->body.y + other->body.h;

	//If any of the sides from A are outside of B
	if (bottomA > topB)
	{
		self->position.y = other->body.y - self->height;
		self->velocity.y = 0;
		self->isGrounded = 1;
		return 1;
	}

	if (topA < bottomB)
	{
		self->position.y = other->body.y + other->body.h - 1;
		return 1;
	}
	if (rightA > leftB)
	{
		self->position.x = other->body.x - self->width;
		return 1;
	}

	if (leftA > rightB)
	{
		self->position.x = other->body.x + other->body.w + 1 ;
		return 1;
	}

	//If none of the sides from A are outside B
	return 0;
}
*/

void body_clear(Body *body)
{
	if (!body)return;
	memset(body, 0, sizeof(Body));
}

void body_set(
	Body       *body,
	char       *name,
	Uint32      layer,
	Uint32      team,
	Vector2D    position,
	Vector2D    velocity,
	float       mass,
	float       gravity,
	float       elasticity,
	Shape *		shape,
	int(*bodyTouch)(struct Body_S *self, struct Body_S *other, Collision *collision),
	int(*worldTouch)(struct Body_S *self, Collision *collision))
{
	if (!body)return;
	body->layer = layer;
	body->team = team;
	vector2d_copy(body->position, position);
	vector2d_copy(body->velocity, velocity);
	body->mass = mass;
	body->gravity = gravity;
	body->elasticity = elasticity;
	body->shape = shape;
	body->bodyTouch = bodyTouch; 
	body->worldTouch = worldTouch;
	gf2d_word_cpy(body->name, name);
}

Space *gf2d_space_new()
{
	Space *space;
	space = (Space *)malloc(sizeof(Space));
	if (!space)
	{
		slog("failed to allocate space for Space");
		return NULL;
	}
	memset(space, 0, sizeof(Space));
	space->bodyList = list_new();
	space->staticShapes = list_new();
	return space;
}

void gf2d_space_add_static_shape(Space *space, Shape shape)
{
	Shape *newShape;
	if (!space)
	{
		slog("no space provided");
		return;
	}
	newShape = (Shape*)malloc(sizeof(shape));
	if (!newShape)
	{
		slog("failed to allocate new space for the shape");
		return;
	}
	memcpy(newShape, &shape, sizeof(Shape));
	space->staticShapes = list_append(space->staticShapes, (void *)newShape);
}

void gf2d_body_push(Body *body, Vector2D direction, float force)
{
	if (!body)return;
	if (body->mass != 0)
	{
		force = force / body->mass;
	}
	vector2d_set_magnitude(&direction, force);
	vector2d_add(body->velocity, body->velocity, direction);
}

void gf2d_space_remove_body(Space *space, Body *body)
{
	if (!space)
	{
		slog("no space provided");
		return;
	}
	if (!body)
	{
		slog("no body provided");
		return;
	}
	if (space->bodyList)
	{
		if (list_delete_data(space->bodyList, (void *)body) != 0)
		{
			slog("failed to remove body named %s from the space", body->name);
		}
	}
}

void gf2d_space_add_body(Space *space, Body *body)
{
	if (!space)
	{
		slog("no space provided");
		return;
	}
	if (!body)
	{
		slog("no body provided");
		return;
	}
	space->bodyList = list_append(space->bodyList, (void *)body);
}

void gf2d_body_draw(Body *body)
{
	Vector4D color;
	Shape shape;
	if (!body)return;
	vector4d_set(color, 0, 255, 255, 255);
	// draw center point
	gf2d_draw_pixel(body->position, color);

	vector4d_set(color, 255, 0, 255, 255);
	gf2d_shape_copy(&shape, *body->shape);
	gf2d_shape_move(&shape, body->position);
	gf2d_shape_draw(shape, gf2d_color_from_vector4(color));
}

void gf2d_free_shapes(void *data, void *context)
{
	Shape *shape;
	if (!data)return;
	shape = (Shape*)data;
	free(shape);
}

void gf2d_space_free(Space *space)
{
	if (!space)return;
	list_delete(space->bodyList);// bodies are not owned by the space and so will not be deleted by the space

									  //static shapes ARE owned by the space, so are deleted when the space goes away
	list_foreach(space->staticShapes, gf2d_free_shapes, NULL);
	list_delete(space->staticShapes);
	free(space);
}

void gf2d_space_draw(Space *space)
{
	int i, count;
	if (!space)
	{
		slog("no space provided");
		return;
	}
	gf2d_draw_rect(gf2d_rect_to_sdl_rect(space->bounds), vector4d(255, 0, 0, 255));
	count = list_get_count(space->bodyList);
	for (i = 0; i < count; i++)
	{
		gf2d_body_draw((Body *)list_get_nth(space->bodyList, i));
	}
	count = list_get_count(space->staticShapes);
	for (i = 0; i < count; i++)
	{
		gf2d_shape_draw(*(Shape *)list_get_nth(space->staticShapes, i), gf2d_color8(0, 255, 0, 255));
	}
}

Vector2D gf2d_body_normal(Body *body, Vector2D poc, Vector2D *normal)
{
	Vector2D n = { 0,0 };
	// given the point of contact make sure the normal points Away from the body
	if (!body)return n;
	if (!normal)
	{
		// calculate based on relative position of POC
		n.x = poc.x - body->position.x;
		n.y = poc.y - body->position.y;
		vector2d_normalize(&n);
		return n;
	}
	vector2d_copy(n, (*normal));
	if ((normal->x > 0) && (body->position.x < poc.x))
	{
		n = vector2d_rotate(n, M_PI);
		return n;
	}
	if ((normal->x < 0) && (body->position.x > poc.x))
	{
		n = vector2d_rotate(n, M_PI);
		return n;
	}
	if ((normal->y > 0) && (body->position.y < poc.y))
	{
		n = vector2d_rotate(n, M_PI);
		return n;
	}
	if ((normal->y < 0) && (body->position.y > poc.y))
	{
		n = vector2d_rotate(n, M_PI);
		return n;
	}
	return n;
}

void gf2d_body_adjust_bounds_collision_velocity(Body *a, Vector2D poc, Vector2D normal)
{
	Vector2D epsilon;

	normal = gf2d_body_normal(a, poc, &normal);

	vector2d_copy(epsilon, normal);
	vector2d_set_magnitude(&epsilon, GF2D_EPSILON);
	vector2d_add(a->position, a->position, epsilon);
	if (normal.x > GF2D_EPSILON)
	{
		a->newVelocity.x = fabs(a->newVelocity.x);
	}
	else if (normal.x < -GF2D_EPSILON)
	{
		a->newVelocity.x = -fabs(a->newVelocity.x);
	}
	if (normal.y > GF2D_EPSILON)
	{
		a->newVelocity.y = fabs(a->newVelocity.y);
	}
	else if (normal.y < -GF2D_EPSILON)
	{
		a->newVelocity.y = -fabs(a->newVelocity.y);
	}
}

void gf2d_body_adjust_static_bounce_velocity(Body *a, Shape *s, Vector2D poc, Vector2D normal)
{
	double phi;//contact angle
	double theta1, theta2;// movement angles
	double v1, v2, part1;
	Vector2D nv;
	if ((!a) || (!s))return;
	normal = gf2d_body_normal(a, poc, &normal);
	v1 = vector2d_magnitude(a->velocity);
	v2 = 0;
	theta1 = vector2d_angle(a->velocity)*GF2D_DEGTORAD;
	theta2 = 0;
	phi = vector2d_angle(normal)*GF2D_DEGTORAD;
	part1 = (v1*cos(theta1 - phi)*(a->mass - 100000) + 2 * 100000 * v2*cos(theta2 - phi)) / (a->mass + 100000);
	nv.x = part1*cos(phi) + v1*sin(theta1 - phi)*cos(phi + GF2D_HALF_PI);
	nv.y = part1*sin(phi) + v1*sin(theta1 - phi)*sin(phi + GF2D_HALF_PI);
	vector2d_copy(a->newVelocity, nv);
}

void gf2d_body_adjust_collision_overlap(Body *a, float slop, Rect bounds)
{
	Rect r;
	if (!a)return;
	gf2d_shape_get_bounds(*a->shape);
	vector2d_add(r, r, a->position);
	if (r.x < bounds.x)r.x = bounds.x + slop;
	if (r.y < bounds.y)r.y = bounds.y + slop;
	if (r.x + r.w > bounds.x + bounds.w)r.x = bounds.x + bounds.w - r.w - slop;
	if (r.y + r.h > bounds.y + bounds.h)r.y = bounds.y + bounds.h - r.h - slop;
}

void gf2d_body_adjust_collision_bounds_velocity(Body *a, float slop, Rect bounds, Vector2D *velocity)
{
	Rect r;
	if (!a)return;
	gf2d_shape_get_bounds(*a->shape);
	vector2d_add(r, r, a->position);
	vector2d_add(r, r, (*velocity));
	if ((r.x <= bounds.x + slop) && (velocity->x < 0))velocity->x = 0;
	if ((r.y <= bounds.y + 2) && (velocity->y < 0))
	{
		slog("would collide with upper bounds");
		velocity->y = 0;
	}
	if ((r.x + r.w >= bounds.x + bounds.w - slop) && (velocity->x > 0))velocity->x = 0;
	if ((r.y + r.h >= bounds.y + bounds.h - slop) && (velocity->y > 0))
	{
		velocity->y = 0;
		slog("would collide with lower bounds");
	}
}


void gf2d_body_adjust_collision_velocity(Body *a, Body *b, Vector2D poc, Vector2D normal)
{
	double phi;//contact angle
	double theta1, theta2;// movement angles
	double v1, v2;
	double part1;
	Vector2D nv;
	if ((!a) || (!b))return;
	normal = gf2d_body_normal(a, poc, &normal);
	v1 = vector2d_magnitude(a->velocity);
	if (b->isActive == 0)
	{
		v2 = 0;
	}
	else v2 = vector2d_magnitude(b->velocity);
	theta1 = vector2d_angle(a->velocity)*GF2D_DEGTORAD;
	theta2 = vector2d_angle(b->velocity)*GF2D_DEGTORAD;
	phi = vector2d_angle(normal)*GF2D_DEGTORAD;
	part1 = (v1*cos(theta1 - phi)*(a->mass - b->mass) + 2 * b->mass*v2*cos(theta2 - phi)) / (a->mass + b->mass);
	nv.x = part1*cos(phi) + v1*sin(theta1 - phi)*cos(phi + GF2D_HALF_PI);
	nv.y = part1*sin(phi) + v1*sin(theta1 - phi)*sin(phi + GF2D_HALF_PI);
	vector2d_copy(a->newVelocity, nv);
}

Uint8 gf2d_body_static_collide(Body *a, Shape *s, Vector2D *poc, Vector2D *normal)
{
	Shape aS;
	if ((!a) || (!s))return 0;
	// set shapes based on each body's current position
	gf2d_shape_copy(&aS, *a->shape);
	gf2d_shape_move(&aS, a->position);

	return gf2d_shape_overlap_poc(aS, *s, poc, normal);
}

Uint8 gf2d_body_collide(Body *a, Body *b, Vector2D *poc, Vector2D *normal)
{
	Shape aS, bS;
	if ((!a) || (!b))return 0;
	// set shapes based on each body's current position
	gf2d_shape_copy(&aS, *a->shape);
	gf2d_shape_move(&aS, a->position);

	gf2d_shape_copy(&bS, *b->shape);
	gf2d_shape_move(&bS, b->position);

	return gf2d_shape_overlap_poc(aS, bS, poc, normal);
}

Uint8 gf2d_body_check_bounds(Body *body, Rect bounds, Vector2D *poc, Vector2D *normal)
{
	Shape aS, bs;
	if (!body)return 0;
	bs = gf2d_shape_from_rect(bounds);

	// set shapes based on each body's current position
	gf2d_shape_copy(&aS, *body->shape);
	gf2d_shape_move(&aS, body->position);

	if (!gf2d_shape_overlap(aS, bs))
	{// we should DEFINITELY be inside the bounds, so return true here
		return 1;
	}
	if (gf2d_edge_intersect_shape_poc(gf2d_edge(bounds.x, bounds.y, bounds.x + bounds.w, bounds.y), aS, poc, normal) ||
		gf2d_edge_intersect_shape_poc(gf2d_edge(bounds.x, bounds.y, bounds.x, bounds.y + bounds.h), aS, poc, normal) ||
		gf2d_edge_intersect_shape_poc(gf2d_edge(bounds.x, bounds.y + bounds.h, bounds.x + bounds.w, bounds.y + bounds.h), aS, poc, normal) ||
		gf2d_edge_intersect_shape_poc(gf2d_edge(bounds.x + bounds.w, bounds.y, bounds.x + bounds.w, bounds.y + bounds.h), aS, poc, normal))
	{
		return 1;
	}
	return 0;
}

void gf2d_body_pre_step(Body *body, Space *space)
{
	if (!body)return;
	if (vector2d_magnitude_squared(body->velocity)< GF2D_EPSILON)
	{
		body->isActive = 0;
	}
	vector2d_copy(body->newVelocity, body->velocity);
}

void gf2d_body_post_step(Body *body, Space *space)
{
	float resistance;
	if (!body)return;
	resistance = 1 - body->elasticity;
	body->newVelocity.x = (body->newVelocity.x * body->elasticity) + (body->velocity.x * resistance);
	body->newVelocity.y = (body->newVelocity.y * body->elasticity) + (body->velocity.y * resistance);
	vector2d_scale(body->newVelocity, body->newVelocity, space->dampening);
	vector2d_copy(body->velocity, body->newVelocity);
}

void gf2d_body_step(Body *body, Space *space, float step)
{
	int i = 0;
	int attempts = 0;
	int collided = 0;
	Collision collision;
	Vector2D poc, normal;
	Vector2D pocB, normalB;
	Vector2D pocS, normalS;
	Body *other, *collider = NULL;
	Shape *shape, *collisionShape = NULL;
	int bodies, staticShapes;
	Vector2D velocity;
	if (!body)return;
	if (!space)return;
	bodies = list_get_count(space->bodyList);
	staticShapes = list_get_count(space->staticShapes);

	vector2d_scale(velocity, body->velocity, space->timeStep);

	//    gf2d_body_adjust_collision_bounds_velocity(body,space->slop,space->bounds,&velocity);

	vector2d_add(body->position, body->position, velocity);
	if (space->precision)
	{
		vector2d_scale(velocity, velocity, 1.0 / space->precision);
	}

	for (attempts = 0; attempts < space->precision; attempts++)
	{
		//bounds check
		if (gf2d_body_check_bounds(body, space->bounds, &pocB, &normalB))
		{
			collided = 1;
			goto attempt;
		}
		//body/body collision check
		for (i = 0; i < bodies; i++)
		{
			other = (Body*)list_get_nth(space->bodyList, i);
			if ((!other) ||// error check
				(other == body))continue;//dont self collide
			if (!(other->layer & body->layer))continue;// only we share a layer
			if ((body->team) && (other->team == body->team))// no friendly fire
				continue;
			if (gf2d_body_collide(body, other, &poc, &normal))
			{
				collider = other;
				goto attempt;
			}
		}
		for (i = 0; i < staticShapes; i++)
		{
			shape = (Shape*)list_get_nth(space->staticShapes, i);
			if (!shape)continue;// error check
			if (gf2d_body_static_collide(body, shape, &pocS, &normalS))
			{
				collisionShape = shape;
				goto attempt;
			}
		}
		// this pass collided with no new things
		break;
	attempt:
		//collision
		vector2d_sub(body->position, body->position, velocity);
	}
	if (((collider) || (collided)) || (collisionShape))
	{
		body->isActive = 0;
	}
	if (collider)
	{
		vector2d_set_magnitude(&velocity, -GF2D_EPSILON);
		vector2d_add(body->position, body->position, velocity);
		if (body->bodyTouch != NULL)
		{
			collision.shape = collider->shape;
			collision.body = collider;
			vector2d_copy(collision.point, poc);
			vector2d_copy(collision.normal, normal);
			collision.timeStep = step;
			body->bodyTouch(body, collider, &collision);
		}
		if (collider->bodyTouch != NULL)
		{
			collision.shape = body->shape;
			collision.body = body;
			vector2d_copy(collision.point, poc);
			vector2d_copy(collision.normal, normal);
			collision.timeStep = step;
			collider->bodyTouch(collider, body, &collision);
		}

		gf2d_body_adjust_collision_velocity(body, collider, poc, normal);
		gf2d_body_adjust_collision_velocity(collider, body, poc, normal);
	}
	if (collisionShape)
	{
		vector2d_set_magnitude(&velocity, -GF2D_EPSILON);
		vector2d_add(body->position, body->position, velocity);
		if (body->worldTouch != NULL)
		{
			body->worldTouch(body, NULL);
		}
		gf2d_body_adjust_static_bounce_velocity(body, collisionShape, pocS, normalS);
	}
	if (collided)
	{
		if (body->worldTouch != NULL)
		{
			body->worldTouch(body, NULL);
		}
		gf2d_body_adjust_collision_overlap(body, space->slop, space->bounds);
	}
}

void gf2d_space_step(Space *space, float t)
{
	int i = 0;
	Body *body;
	int bodies;
	Vector2D gravityStep;
	Vector2D gravityFactor;
	if (!space)return;
	vector2d_scale(gravityStep, space->gravity, space->timeStep);
	bodies = list_get_count(space->bodyList);
	//    slog("updating space step:");
	for (i = 0; i < bodies; i++)
	{
		body = (Body*)list_get_nth(space->bodyList, i);
		if (!body)continue;// body already hit something
		vector2d_scale(gravityFactor, gravityStep, body->gravity);
		vector2d_add(body->velocity, body->velocity, gravityFactor);
		gf2d_body_pre_step(body, space);
	}
	for (i = 0; i < bodies; i++)
	{
		body = (Body*)list_get_nth(space->bodyList, i);
		if ((!body) || (body->isActive))continue;// body already hit something
												 // apply gravity
												 //         if (strcmp(body->name,"player")==0)
												 //         {
												 //                 slog("updating player body");
												 //         }
		gf2d_body_step(body, space, t);
	}
	for (i = 0; i < bodies; i++)
	{
		body = (Body*)list_get_nth(space->bodyList, i);
		if (!body)continue;// body already hit something
		gf2d_body_post_step(body, space);
	}
}

void gf2d_space_update(Space *space)
{
	int i;
	float s;
	Body *body;
	int bodies;
	if (!space)return;
	// reset all body tracking
	bodies = list_get_count(space->bodyList);
	for (i = 0; i < bodies; i++)
	{
		body = (Body*)list_get_nth(space->bodyList, i);
		if (!body)continue;
		body->isActive = 1;
	}
	for (s = 0; s < 1; s += space->timeStep)
	{
		gf2d_space_step(space, s);
	}
}

void gf2d_space_body_collision_test(Space *space, Shape shape, Collision *collision)
{
	int i, count;
	Body *body;
	if ((!space) || (!collision))return;
	count = list_get_count(space->bodyList);
	for (i = 0; i < count; i++)
	{
		body = (Body*)list_get_nth(space->bodyList, i);
		if (!body)continue;
		if (gf2d_body_static_collide(body, &shape, &collision->point, &collision->normal))
		{
			collision->collided = 1;
			collision->body = body;
			collision->shape = body->shape;
			return;
		}
	}
}

void gf2d_space_shape_collision_test(Space *space, Shape shape, Collision *collision)
{
	int i, count;
	Shape *s;
	if ((!space) || (!collision))return;
	count = list_get_count(space->staticShapes);
	for (i = 0; i < count; i++)
	{
		s = (Shape*)list_get_nth(space->staticShapes, i);
		if (!s)continue;
		if (gf2d_shape_overlap_poc(shape, *s, &collision->point, &collision->normal))
		{
			collision->collided = 1;
			collision->body = NULL;
			collision->shape = s;
			return;
		}
	}
}


Collision gf2d_space_shape_test(Space *space, Shape shape)
{
	Collision c;
	c.collided = 0;
	if (!space)return c;
	memset(&c, 0, sizeof(Collision));
	gf2d_space_body_collision_test(space, shape, &c);
	if (c.collided)return c;
	gf2d_space_shape_collision_test(space, shape, &c);
	return c;
}

Space *gf2d_space_new_full(
	int         precision,
	SDL_Rect        bounds,
	float       timeStep,
	Vector2D    gravity,
	float       dampening,
	float       slop)
{
	Space *space;
	space = gf2d_space_new();
	if (!space)return NULL;
	gf2d_rect_copy(space->bounds, bounds);
	vector2d_copy(space->gravity, gravity);
	space->timeStep = timeStep;
	space->precision = precision;
	space->dampening = dampening;
	space->slop = slop;
	return space;
}




int checkBoxCollision(Entity * self, Entity * other)
{
	if (self->body.x + self->body.w < other->body.x || self->body.x > other->body.x + other->body.w ||
		self->body.y + self->body.h < other->body.y || self->body.y > other->body.y + other->body.h)
	{
		self->moveSpeed = 4;
		vector4d_set(self->color, 255, 255, 255, 255);
		return 0;
		
	}
	self->moveSpeed = -4;
	vector4d_set(self->color, 255, 0, 0, 255);
	return 1;
}

int checkCircleCollision(Entity *self, Entity * other)
{
	double positionA, positionB;

	
}

Entity* wall_new(Vector2D position)
{
	Entity * self = entity_new();
	
	vector2d_set(self->position, position.x, position.y);
	self->body.x = position.x;
	self->body.y = position.y;

	self->body.w = 200;
	self->body.h = 400;
	self->type = "wall";

	self->sprite = gf2d_sprite_load_all("images/walls/greyStoneWall.jpg", self->body.w, self->body.h, 1);
	return self;
}