/*
 * Author: Humenius, contact (a) humenius dot me
 * (c) 2020
 * */

#ifndef __PROMETHEUSCLIENT_HPP_
#define __PROMETHEUSCLIENT_HPP_

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

// using namespace prometheus;

class PrometheusClient  {
    public:

        PrometheusClient();
        ~PrometheusClient();

        bool isConfigured() const;

        void send();

        void register_device();

    private:
        prometheus::Exposer _exposer{"127.0.0.1:8081"};
        std::shared_ptr<prometheus::Registry> _registry;

        bool _ready;
};

extern PrometheusClient *prometheusClient;

#endif