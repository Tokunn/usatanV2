#ifndef HEAD_DO_LINETRACE
#define HEAD_DO_LINETRACE


/*===== LineTrace =====*/
class LineTrace
{
    public:
        LineTrace();
        void set_sensor_value(int* p_sensor_value);
        int get_tire_speed_value();

    private:
        int comp_command(const int* p_sensor_value, const int (*p_command)[2]);

        int sensor_value;
        int master_speed;
        int command[0x3F+0x1][2]; // [2] = {LEFT, RIGHT}
};

#endif // HEAD_DO_LINETRACE
