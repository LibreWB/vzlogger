#include <api/Prometheus.hpp>

PrometheusClient *prometheusClient = 0;

PrometheusClient::PrometheusClient() {
    _ready = false;

    _registry = std::make_shared<prometheus::Registry>();

    _ready = true;
}

PrometheusClient::~PrometheusClient() {
    _ready = false;

    _exposer.~Exposer();
    _registry.reset();
    _ready = 0;
}

bool PrometheusClient::isConfigured() const {
    return _ready;
}