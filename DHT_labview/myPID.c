#include"myPID.h"

#define KP (double)20
#define KI (double)0.5
#define KD (double)0.1
#define PWM_PERIOD (uint16_t)10000

static double error_integral = 0;
static double error_derivative = 0;
static double output_pid = 0;
static double last_error;
static double error;
static double max_output;
static double pid_setpoint;
static uint16_t duty_cycle=0;

void PID_setMaxOutput(double max){
	max_output = max;
}

void PID_Controller(double setpoint, double actual)
{
    // Calculate error
    error = setpoint - actual;
    // Update last error
    last_error = (double)error;
    // Calculate integral
    error_integral += (error+last_error);
	
		if (error_integral > max_output) error_integral = max_output;
    // Calculate derivative
    error_derivative = (error - last_error);

    // Calculate PID output
    output_pid = KP*error + KI*error_integral + KD*error_derivative;

    // Set pwm
		if (output_pid > max_output) output_pid = max_output;
		if(output_pid<0) output_pid =(double)(0.0/60.0)*pid_setpoint;
    // Convert output to PWM duty cycle
    duty_cycle = (uint16_t)((output_pid/max_output) * PWM_PERIOD);
    // Set PWM duty cycle
    setDutyCircle(duty_cycle);
}
