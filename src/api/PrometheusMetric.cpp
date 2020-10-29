/**
 * Channel handler for Prometheus metrics collection
 *
 * @package vzlogger
 * @copyright Copyright (c) 2020, The volkszaehler.org project
 * @license http://www.gnu.org/licenses/gpl.txt GNU Public License
 * @author Humenius <contact@humenius.me>
 */

#include <PrometheusClient.hpp>
#include <api/PrometheusMetric.hpp>
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


static const char *OPTION_MEASUREMENT_NAME__KEY = "measurement_name";
static const char *OPTION_LABEL__KEY = "label";
static const char *OPTION_HELP_TEXT__KEY = "help_text";

vz::api::PrometheusMetric::PrometheusMetric(Channel::Ptr ch, std::list<Option> options)
	: ApiIF(ch) {
	OptionList optionList;

	try {
		_description.measurementName =
			optionList.lookup_string(options, OPTION_MEASUREMENT_NAME__KEY);
	} catch (vz::OptionNotFoundException &e) {
		std::ostringstream _textStringStream;
		_textStringStream << "PrometheusMetric requires parameter \""
						  << OPTION_MEASUREMENT_NAME__KEY << "\" but it's missing";
		print(log_error, _textStringStream.str().c_str(), ch->name());
		throw;
	} catch (vz::VZException &e) {
		std::ostringstream _textStringStream;
		_textStringStream << "PrometheusMetric requires parameter \""
						  << OPTION_MEASUREMENT_NAME__KEY
						  << "\" but its type does not equal a string";
		print(log_error, _textStringStream.str().c_str(), ch->name());
		throw;
	}

	try {
		_description.label = optionList.lookup_string(options, OPTION_LABEL__KEY);
	} catch (vz::OptionNotFoundException &e) {
		std::ostringstream _textStringStream;
		_textStringStream << "PrometheusMetric requires parameter \"" << OPTION_LABEL__KEY
						  << "\" but it's missing";
		print(log_error, _textStringStream.str().c_str(), ch->name());
		throw;
	} catch (vz::VZException &e) {
		std::ostringstream _textStringStream;
		_textStringStream << "PrometheusMetric requires parameter \"" << OPTION_LABEL__KEY
						  << "\" but its type does not equal a string";
		print(log_error, _textStringStream.str().c_str(), ch->name());
		throw;
	}

	try {
		_description.helpText = optionList.lookup_string(options, OPTION_HELP_TEXT__KEY);
	} catch (vz::OptionNotFoundException &e) {
		std::ostringstream _textStringStream;
		_textStringStream << "PrometheusMetric requires parameter \"" << OPTION_HELP_TEXT__KEY
						  << "\" but it's missing";
		print(log_error, _textStringStream.str().c_str(), ch->name());
		throw;
	} catch (vz::VZException &e) {
		std::ostringstream _textStringStream;
		_textStringStream << "PrometheusMetric requires parameter \"" << OPTION_HELP_TEXT__KEY
						  << "\" but its type does not equal a string";
		print(log_error, _textStringStream.str().c_str(), ch->name());
		throw;
	}

	_counter = PrometheusClient::GetInstance()->RegisterMetrics(this);
}

vz::api::PrometheusMetric::~PrometheusMetric() { _counter = nullptr; }

void vz::api::PrometheusMetric::send() {
	Channel::Ptr ch = channel();
	Buffer::Ptr buffer = ch->buffer();

	buffer->lock();
	const Buffer::iterator &lastEntry = buffer->end();
	print(log_finest, "Reading buffer: timestamp %lld - value %f", ch->name(), lastEntry->time_ms(),
		  lastEntry->value());
	_counter->Increment(lastEntry->value());
	lastEntry->mark_delete();
	buffer->unlock();
}

void vz::api::PrometheusMetric::register_device() { /* No impl */ }