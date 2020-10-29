/**
 * Management of Prometheus registry and metrics collection
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

#ifndef __PROMETHEUSCLIENT_HPP_
#define __PROMETHEUSCLIENT_HPP_

#include <api/PrometheusMetric.hpp>
#include <prometheus/counter.h>
#include <prometheus/metric_family.h>
#include <prometheus/registry.h>

class PrometheusClient {
  public:
	PrometheusClient(PrometheusClient &other) = delete;
	void operator=(PrometheusClient &other) = delete;

	/**
	 * Register a Prometheus metric to registry.
	 * If `metricPtr` is already added, its labels will be appended instead.
	 *
	 * @param metricPtr Metrics to be registered
	 * @return Pointer to created counter that was added to a counter family
	 */
	std::unique_ptr<prometheus::Counter> RegisterMetrics(vz::api::PrometheusMetric *metricPtr);

	static PrometheusClient *GetInstance() {
		if (!instance)
			instance = new PrometheusClient();
		return instance;
	};

	/**
	 * Returns a vector with all results created by calling `prometheus::Counter#Collect()`
	 * on registry. Calling `Collect()` on `prometheus::Registry` should be thread-safe.
	 * @return Vector of collected metric families ready to be serialized
	 */
	std::vector<prometheus::MetricFamily> CollectMetrics();

  private:
	static PrometheusClient *instance;

	PrometheusClient();
	~PrometheusClient();

  private:
	const char *LOG_NAME = "PrometheusClient";

	std::vector<prometheus::Family<prometheus::Counter> *> _familyCounters;
	std::shared_ptr<prometheus::Registry> _registry;
}; // class PrometheusClient

#endif /* __PROMETHEUSCLIENT_HPP_ */
