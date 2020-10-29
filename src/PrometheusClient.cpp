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

#include <PrometheusClient.hpp>

PrometheusClient *PrometheusClient::instance = nullptr;

PrometheusClient::PrometheusClient() {
    print(log_debug, "Initializing PrometheusClient for Prometheus metrics", LOG_NAME);

	_registry = std::make_shared<prometheus::Registry>();
}

PrometheusClient::~PrometheusClient() {
    _registry.reset();

	for (auto familyCounter : _familyCounters) {
		delete &familyCounter;
		familyCounter = nullptr;
	}
	_familyCounters.clear();
}

std::vector<prometheus::MetricFamily> PrometheusClient::CollectMetrics() {
    auto collectedMetrics = std::vector<prometheus::MetricFamily>{};

    auto metrics = _registry->Collect();
    collectedMetrics.insert(collectedMetrics.end(),
                            std::make_move_iterator(metrics.begin()),
                            std::make_move_iterator(metrics.end()));

    return collectedMetrics;
}

std::unique_ptr<prometheus::Counter>
PrometheusClient::RegisterMetrics(vz::api::PrometheusMetric *metricPtr) {
    vz::api::PrometheusMetricDescription *description = metricPtr->description();
    prometheus::Family<prometheus::Counter> *familyCounter;

    for (auto &_familyCounter : _familyCounters) {
        if (_familyCounter->GetName() == description->measurementName) {
            familyCounter = _familyCounter;

            print(log_debug,
                  R"(Existing counter family "%s" found. Will append labels to existing family.)",
                  description->measurementName.c_str(), LOG_NAME);
        }
    }

    if (!familyCounter) {
        familyCounter = &prometheus::BuildCounter()
            .Name(description->measurementName)
            .Help(description->helpText)
            .Register(*_registry);
        _familyCounters.push_back(familyCounter);

        print(log_debug, R"(Counter family %s does not exist. Created new one.)",
              description->measurementName.c_str(), LOG_NAME);
    }

    // FIXME What is "value" in labels? Data type? Description of value?
    // Also see: https://stackoverflow.com/questions/52883657/usage-guidelines-for-prometheus-c
    std::unique_ptr<prometheus::Counter> counter(
        &familyCounter->Add({{description->label, "watt"}}));
    print(log_debug, R"(Appended label "%s" to counter family "%s" and created unique pointer.)",
          description->label.c_str(), description->measurementName.c_str(), LOG_NAME);

    return counter;
}
