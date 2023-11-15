#define SCREENW 800
#define SCREENH 600

#define MIN_RAD 10
#define MAX_RAD 20

#define MAX_VEL 100

#include <cmath>
#include <vector>

#include <supernova/constants.h>
#include <supernova/engine.h>
#include <supernova/enums.h>


using namespace std;



class Particle {
	public:
		const int DENSITY = 3; // In mass/pixel^2
		const double MAX_K = 0.5*DENSITY*PI*MAX_RAD*MAX_RAD*MAX_VEL;

		int radius;
		float mass;
		Vector pos;
		Vector vel;

		Particle() {};
		Particle(const Vector pos);

		void update(double dt);
		void draw(Renderer &renderer);
		void collide(Particle &particle);
		void collide_walls();
		double kinetic_energy();
		double colour_factor();
};

Particle::Particle(const Vector pos) {
	this->radius = randint(MIN_RAD, MAX_RAD);
	this->mass = DENSITY*PI*pow(this->radius, 2);
	this->pos = pos;
	this->vel = Vector{MAX_VEL, 0}.rotate(randint(0, 360));
}

void Particle::update(double dt) {
	pos += vel*dt;

	collide_walls();
}

void Particle::draw(Renderer &renderer) {
	renderer.draw_circle({pos, radius}, {Uint8(colour_factor()), Uint8(255 - colour_factor()), 0, 255});
}

void Particle::collide(Particle &particle) {
	double ds = (radius + particle.radius) - pos.distance_to(particle.pos);
	if (ds >= 0) {
		pos -= vel.normalize()*ds;
		double temp = vel.x;
		vel.x = ((mass - particle.mass)*vel.x + 2*particle.mass*particle.vel.x)/(mass + particle.mass);
		particle.vel.x = ((particle.mass - mass)*particle.vel.x + 2*mass*temp)/(mass + particle.mass);
		temp = vel.y;
		vel.y = ((mass - particle.mass)*vel.y + 2*particle.mass*particle.vel.y)/(mass + particle.mass);
		particle.vel.y = ((particle.mass - mass)*particle.vel.y + 2*mass*temp)/(mass + particle.mass);
	}
}

void Particle::collide_walls() {
	if (pos.x < radius) {
		pos.x = radius;
		vel.x = -vel.x;
	} else if (pos.x > SCREENW - radius) {
		pos.x = SCREENW - radius;
		vel.x = -vel.x;
	}
	if (pos.y < radius) {
		pos.y = radius;
		vel.y = -vel.y;
	} else if (pos.y > SCREENH - radius) {
		pos.y = SCREENH - radius;
		vel.y= -vel.y;
	}
}

double Particle::kinetic_energy() {
	return 0.5*mass*vel.magnitude_squared();
}

double Particle::colour_factor() {
	return (kinetic_energy()/MAX_K)*255;
}


int main(int, char **) {

	Engine engine;

	Window window("Particles in a box", {SCREENW, SCREENH});
	Renderer renderer(window);

	Clock clock;
	Events events;
	Mouse mouse = Mouse(LEFT);

	bool running = true;
	double dt;

	vector<Particle> particles;

	while (running) {
		dt = clock.tick(60);

		running = events.process_events(&EVENT_KEYS, &mouse);

		if (mouse.buttons[LEFT].pressed) {
			Particle particle = Particle(mouse.pos);
			particles.push_back(particle);
		}

		for (int i = 0; i < particles.size(); i++) {
			particles[i].update(dt);
		}

		for (int i = 0; i < particles.size(); i++) {
			for (int j = i + 1; j < particles.size(); j++) {
				particles[i].collide(particles[j]);
			}
		}

		renderer.clear({200, 200, 200, 255});
		for (int i = 0; i < particles.size(); i++) {
			particles[i].draw(renderer);
		}
		renderer.present();
	}

    return 0;
}
