#include "minunit.h"
#include "strategie.h"

MU_TEST(test_calcul_prochaine_action_exist)
{
    /* Test that calcul_prochaine_action() returns a valid action string */
    const char *action = calcul_prochaine_action();
    mu_assert(action != NULL, "calcul_prochaine_action() should not return NULL");
    mu_assert(strcmp(action, "TURN_RIGHT") == 0 || strcmp(action, "TURN_LEFT") == 0 ||
                  strcmp(action, "ACCELERATE") == 0 || strcmp(action, "DECELERATE") == 0 || strcmp(action, "WAIT") == 0,
              "calcul_prochaine_action() should return a valid action string");
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_calcul_prochaine_action_exist);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}