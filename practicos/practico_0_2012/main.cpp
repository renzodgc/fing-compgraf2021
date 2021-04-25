// Global dependencies
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cmath>

// Local dependencies
#include <handlers/vector_operations_handler.h>
#include <models/vector.h>
#include <handlers/log_handler.h>
#include <const.h>

#define G 9.81

// Main method
int main(int argc, char** argv){
	if (argc < 5) {
		error_msg(ERROR_MAIN_BAD_FORMATTING);
		exit (EXIT_FAILURE);
	}
	
	// Read arguments
	const float x_vel = atof(argv[1]);
	const float y_vel = atof(argv[2]);
	const float z_vel = atof(argv[3]);
    const float delta_time = atof(argv[4]);
    printf("\n");
    printf("Initial velocities are:(%f m/s, %f m/s, %f m/s)\n", x_vel, y_vel, z_vel);
    printf("Updated every: %f\n", delta_time);
    printf("\n");

    // Variables
    const float sq_delta_time = pow(delta_time, 2);
    float time = 0;
    Vector projectile;
    Vector projectile_translation;
    projectile.set_x(0);
    projectile.set_y(0);
    projectile.set_z(0);

    // Calculate projectile trajectory
    projectile_translation.set_x(x_vel*delta_time);
    projectile_translation.set_y(y_vel*delta_time);
    projectile_translation.set_z(z_vel*delta_time);
    do {
        printf("Time: %f seconds\n", time);
        printf("Vector: (%f, %f, %f)\n", projectile.get_x(), projectile.get_y(), projectile.get_z());
        printf("\n");

        projectile_translation.set_z(projectile_translation.get_z() - 0.5*G*sq_delta_time);

        VectorOperationsHandler::vector_sum(projectile, projectile_translation, projectile);
        time += delta_time;
    }
    while(projectile.get_z() > 0);

    printf("Projectile has reached zero altitude\n");
	return OK;
}