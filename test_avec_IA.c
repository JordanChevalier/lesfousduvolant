for (;;)
{

    float game_time;
    int exploration;
    float x, y;
    float orientation;
    float speed;
    float front, right, rear, left;

    /* -------------------- Lire capteurs -------------------- */

    if (send_line(fd, "GET_SENSORS") < 0)
        goto done;

    if (read_line(fd, line, sizeof(line)) < 0)
        goto done;

    int n = sscanf(line, "%f %d %f %f %f %f %f %f %f %f", &game_time, &exploration, &x, &y, &orientation, &speed,
                   &front, &right, &rear, &left);

    if (n != 10)
    {
        printf("Erreur capteurs : %s\n", line);
        continue;
    }

    printf("Front=%.2f Right=%.2f Left=%.2f Speed=%.2f Orientation=%.2f\n", front, right, left, speed, orientation);

    /* ==================== STRATEGIE ==================== */

    /* Mur proche → ralentir + tourner de 90° */
    if (front <= 0.2f)
    {
        const char *direction;

        if (rand() % 2)
            direction = "TURN_LEFT";
        else
            direction = "TURN_RIGHT";

        printf("Virage 90° %s\n", direction);

        /* ralentir avant le virage */
        while (speed > 0.2f)
        {
            if (send_line(fd, "DECELERATE") < 0)
                goto done;

            if (read_line(fd, line, sizeof(line)) < 0)
                goto done;

            speed -= 0.1f;
        }

        /* tourner de 90° : 9 × 10° */
        for (int i = 0; i < 9; i++)
        {
            if (send_line(fd, direction) < 0)
                goto done;

            if (read_line(fd, line, sizeof(line)) < 0)
                goto done;

            if (strcmp(line, "OK") != 0 && strcmp(line, "KO") != 0 && strcmp(line, "BLOCKED") != 0)
            {
                printf("Server: %s\n", line);
                goto done;
            }
        }
    }

    /* Grande ligne droite → accélération progressive */
    else if (front > 2.0f)
    {
        /* vitesse max volontairement limitée */
        if (speed < 0.5f)
        {
            if (send_line(fd, "ACCELERATE") < 0)
                goto done;

            if (read_line(fd, line, sizeof(line)) < 0)
                goto done;

            printf("ACCELERATE -> %s\n", line);
        }
    }

    /* Mur qui approche → ralentir */
    else if (front < 0.8f)
    {
        if (speed > 0.2f)
        {
            if (send_line(fd, "DECELERATE") < 0)
                goto done;

            if (read_line(fd, line, sizeof(line)) < 0)
                goto done;

            printf("DECELERATE -> %s\n", line);
        }
    }

    /* Zone intermédiaire → garder la vitesse actuelle */
    else
    {
        printf("Maintien vitesse\n");
    }
}