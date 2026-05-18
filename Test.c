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

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_calcul_prochaine_action_exist);
    MU_RUN_TEST(test_get_sensors);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}