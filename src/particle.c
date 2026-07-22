
#define WIDTH 80
#define HEIGHT 24
#define MAX_PARTICLES 250

typedef struct {
    float x, y;
    float vx, vy;
    int life;
} Particle;

Particle particles[MAX_PARTICLES];

int kraw_particles (char **args)
{
    srand(time(NULL));

    printf("\033[2J");

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            int p = rand() % MAX_PARTICLES;

            particles[p].x = rand() % WIDTH;
            particles[p].y = 0;

            particles[p].vx = ((rand() % 100) / 100.0f) - 0.5f;
            particles[p].vy = 0.2f + (rand() % 100) / 200.0f;

            particles[p].life = 40;
        }

        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (particles[i].life > 0)
            {
                particles[i].x += particles[i].vx;
                particles[i].y += particles[i].vy;

                particles[i].vy += 0.02f;   // gravity
                particles[i].life--;
            }
        }

        printf("\033[H");

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                char c = ' ';

                for (int i = 0; i < MAX_PARTICLES; i++)
                {
                    if (particles[i].life > 0 &&
                        (int)particles[i].x == x &&
                        (int)particles[i].y == y)
                    {
                        if (particles[i].life > 25)
                            c = '*';
                        else if (particles[i].life > 10)
                            c = '+';
                        else
                            c = '.';
                    }
                }

                putchar(c);
            }

            putchar('\n');
        }

        usleep(30000);
    }

    return 0;
}