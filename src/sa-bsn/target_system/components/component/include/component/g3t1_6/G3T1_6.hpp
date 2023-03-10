#ifndef G3T1_6_HPP
#define G3T1_6_HPP

#include <string>
#include <exception>

#include "ros/ros.h"

#include "libbsn/range/Range.hpp"
#include "libbsn/resource/Battery.hpp"
#include "libbsn/generator/Markov.hpp"
#include "libbsn/generator/DataGenerator.hpp"
#include "libbsn/filters/MovingAverage.hpp"
#include "libbsn/utils/utils.hpp"
#include "libbsn/configuration/SensorConfiguration.hpp"

#include "component/Sensor.hpp"

#include "messages/SensorData.h"
#include "services/PatientData.h"

class G3T1_6 : public Sensor {
    	
  	public:
    	G3T1_6(int &argc, char **argv, const std::string &name);
    	virtual ~G3T1_6();

	private:
      	G3T1_6(const G3T1_6 &);
    	G3T1_6 &operator=(const G3T1_6 &);

		std::string label(double &risk);
    
	public:
		virtual void setUp();
    	virtual void tearDown();

        double collect();
        double process(const double &data);
        void transfer(const double &data);
		void failure_check(const messages::SensorData::ConstPtr& sensor_data);

  	private:
		bsn::generator::Markov markov;
		bsn::generator::DataGenerator dataGenerator;		
		bsn::filters::MovingAverage filter;
		bsn::configuration::SensorConfiguration sensorConfig;

		ros::NodeHandle handle;
		ros::Publisher data_pub;
		ros::Subscriber glucosemeterSub;
		ros::ServiceClient client;	

		double collected_risk;

};

#endif 
