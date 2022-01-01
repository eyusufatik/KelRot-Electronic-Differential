class SteeringWheel{
    private:
        volatile long *encoderStep;
        double angle;
    protected:

    public:
        SteeringWheel(volatile long *step){
            this->encoderStep = step;
        }
        double getAngle(){
            this->angle = (double) *encoderStep * 1.0/2400.0 * 2.0 * PI;
            return angle;
        }
};
