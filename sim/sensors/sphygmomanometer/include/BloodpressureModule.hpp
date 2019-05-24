#ifndef BLOODPRESSURE_MODULE_HPP
#define BLOODPRESSURE_MODULE_HPP

#include <fstream>
#include <chrono>
#include <string>
#include <iostream>

#include "ros/ros.h"

#include "range/Range.hpp"
#include "resource/Battery.hpp"
#include "generator/Markov.hpp"
#include "filters/MovingAverage.hpp"
#include "operation/Operation.hpp"
#include "configuration/SensorConfiguration.hpp"

#include "bsn/SensorData.h"
#include "bsn/SensorData.h"
#include "bsn/TaskInfo.h"
#include "bsn/ContextInfo.h"
#include "bsn/ControlCommand.h"

class BloodpressureModule {
    
	private:
      	BloodpressureModule(const BloodpressureModule &);
    	BloodpressureModule &operator=(const BloodpressureModule &);
    	
    	virtual void tearDown();

		void sendTaskInfo(const std::string &/*task_id*/, const double &/*cost*/, const double &/*reliability*/, const double &/*frequency*/);
		void sendContextInfo(const std::string &/*context_id*/, const bool &/*value*/);

		void sendMonitorTaskInfo(const std::string &/*task_id*/, const double &/*cost*/, const double &/*reliability*/, const double &/*frequency*/);
		void sendMonitorContextInfo(const std::string &/*context_id*/, const bool &/*value*/);

  	public:
		virtual void setUp();

    	BloodpressureModule(const int32_t &argc, char **argv);
    	virtual ~BloodpressureModule();

    	void run();

  	private:
	  	void receiveControlCommand(const bsn::ControlCommand::ConstPtr& msg);
		
		std::string type;
		bsn::resource::Battery battery;
		bool available;

		double diasdata_accuracy;
		double diascomm_accuracy;
		double systdata_accuracy;
		double systcomm_accuracy;

		bool active;
		std::map<std::string,double> params;

		bsn::generator::Markov markovSystolic;
		bsn::generator::Markov markovDiastolic;
		bsn::filters::MovingAverage filterSystolic;
		bsn::filters::MovingAverage filterDiastolic;
		bsn::configuration::SensorConfiguration sensorConfigSystolic;
		bsn::configuration::SensorConfiguration sensorConfigDiastolic;

		int persist;
		std::string path;
		std::ofstream fp;

		ros::Publisher taskPub, contextPub, dataPub;
};

#endif 