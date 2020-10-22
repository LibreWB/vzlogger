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

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/family.h>
#include <prometheus/metric_family.h>
#include <prometheus/registry.h>

#include <Channel.hpp>
#include <api/PrometheusMetric.hpp>
#include <common.h>

class PrometheusClient {
  public:
	// bool isConfigured() const;
	// typedef vz::shared_ptr<vz::ApiIF> Ptr;

	PrometheusClient(PrometheusClient &other) = delete;
	// void operator=(PrometheusClient &other) = delete;

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

  private:
	static PrometheusClient *instance;

	PrometheusClient();
	~PrometheusClient();

  private:
	const char *LOG_NAME = "PrometheusClient";

	prometheus::Exposer _exposer{"127.0.0.1:8081"};
	std::vector<prometheus::Family<prometheus::Counter>> _familyCounters;
	std::shared_ptr<prometheus::Registry> _registry;

	bool _ready;
}; // class PrometheusClient

#endif /* __PROMETHEUSCLIENT_HPP_ */
