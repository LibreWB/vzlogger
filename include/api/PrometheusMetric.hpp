/**
 * Channel handler for Prometheus metrics collection
 *
 * @package vzlogger
 * @copyright Copyright (c) 2020, The volkszaehler.org project
 * @license http://www.gnu.org/licenses/gpl.txt GNU Public License
 * @author Humenius <contact@humenius.me>
 */

/*
 * This file is part of volkzaehler.org
 *
 * volkzaehler.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * volkzaehler.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with volkszaehler.org. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __PROMETHEUSMETRICS_HPP_
#define __PROMETHEUSMETRICS_HPP_

#include <ApiIF.hpp>
#include <Options.hpp>
#include <VZException.hpp>
#include <common.h>
#include <prometheus/counter.h>

namespace vz {
namespace api {

struct PrometheusMetricDescription {
	std::string measurementName;
	std::string label;
	std::string helpText;
};

class PrometheusMetric : public ApiIF {
  public:
	typedef vz::shared_ptr<PrometheusMetric> Ptr;

	PrometheusMetric(Channel::Ptr ch, std::list<Option> options);
	~PrometheusMetric();

	/**
	 * Initialize the counter by registering itself to `PrometheusClient` and store it in this
	 * object
	 * @param prometheusClient Instance of `PrometheusClient`
	 */
	// void InitCounter(PrometheusClient *prometheusClient);

	void send() override;

	void register_device() override;

	PrometheusMetricDescription *description() { return &_description; };

  private:
	PrometheusMetricDescription _description;
	std::unique_ptr<prometheus::Counter> _counter;
};
} // namespace api
} // namespace vz

#endif /* __PROMETHEUSMETRICS_HPP_ */
