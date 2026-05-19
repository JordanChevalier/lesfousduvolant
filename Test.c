#include "minunit.h"
#include "strategie.h"

MU_TEST(test_calcul_prochaine_action_exist)
{
    /* Test that calcul_prochaine_action() returns a valid action string */
    const char *action = calcul_prochaine_action();
    mu_assert(action != NULL, "calcul_prochaine_action() should not return NULL");
}
MU_TEST(test_get_sensors)
{
    const char *sensors = generate_get_sensors();
    mu_assert_string_eq(sensors, "GET_SENSORS");
}

MU_TEST(test_analyse_sensors)
{
    /* Test that analyse_sensors() can be called without crashing */
    analyse_sensors("33.70 1 5.50 4.20 180 1.10 1.00 1.00 2.00 2.00");

    mu_assert_int_eq(sensor_time * 100, 33.70 * 100);
    mu_assert_int_eq(sensor_exploration, 1);
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_calcul_prochaine_action_exist);
    MU_RUN_TEST(test_get_sensors);
    MU_RUN_TEST(test_analyse_sensors);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}