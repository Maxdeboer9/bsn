#ifndef G3T1_3_HPP
#define G3T1_3_HPP

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

class G3T1_3 : public Sensor {
    	
  	public:
    	G3T1_3(int &argc, char **argv, const std::string &name);
    	virtual ~G3T1_3();

	private:
      	G3T1_3(const G3T1_3 &);
    	G3T1_3 &operator=(const G3T1_3 &);

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
		ros::Subscriber thermometerSub;
		ros::ServiceClient client;	

		double collected_risk;

};

#endif 