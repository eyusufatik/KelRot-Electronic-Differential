class DriveWheel{
    private:
        volatile long *encoderStep;
        double radius;
        long lastStep;
        long lastTime;
    protected:

    public:
        DriveWheel(volatile long *step, double radiusOfWheel){
            this->encoderStep = step;
            this->radius = radiusOfWheel;
        }
        double getSpeed(){
            return getAngularSpeed() * radius;
        }
        double getAngularSpeed(){
            long step = *encoderStep;
            long currentTime = micros();
            double degreeDiff = (double) (step - lastStep) * 1.0/2400.0 * 2.0 * PI;
            double timeDiff = (double) (currentTime - lastTime) / 1000000.0;
            double angularSpeed = degreeDiff / timeDiff;

            this->lastStep = step;
            this->lastTime = currentTime;
            return angularSpeed;
        }
};
