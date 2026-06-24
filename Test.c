#include "minunit.h"
#include "strategie.h"

/* ================= TEST ================= */

MU_TEST(test_parse)
{
    reset_strategy();

    analyse_sensors("10.50 1 2.0 3.0 90 0.5 1.0 2.0 3.0 4.0");

    mu_assert_int_eq(sensor_exploration, 1);
    mu_assert_int_eq(sensor_x, 200);
    mu_assert_int_eq(sensor_y, 300);
}

/* ================= INIT ================= */

MU_TEST(test_init)
{
    reset_strategy();
    const char *a = calcul_prochaine_action();
    mu_assert_string_eq(a, "GET_SENSORS");
}

/* ================= SUITE ================= */

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_parse);
    MU_RUN_TEST(test_init);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}