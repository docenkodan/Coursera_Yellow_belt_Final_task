#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (comparison_ == Comparison::Less) {
		return date < date_;
	} else if (comparison_ == Comparison::LessOrEqual) {
		return !(date > date_);
	} else if (comparison_ == Comparison::Greater) {
		return date > date_;
	} else if (comparison_ == Comparison::GreaterOrEqual) {
		return !(date < date_);
	} else if (comparison_ == Comparison::Equal) {
		return !(date < date_) && !(date > date_);
	} else {
		return (date < date_) || (date > date_);
	}
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (event.empty()) {
		return false;
	}
	if (comparison_ == Comparison::Less) {
		return event < event_;
	} else if (comparison_ == Comparison::LessOrEqual) {
		return event <= event_;
	} else if (comparison_ == Comparison::Greater) {
		return event > event_;
	} else if (comparison_ == Comparison::GreaterOrEqual) {
		return event >= event_;
	} else if (comparison_ == Comparison::Equal) {
		return event == event_;
	} else {
		return event != event_;
	}
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	bool left_b = left_->Evaluate(date, event);
	bool right_b = right_->Evaluate(date, event);
	if (logical_operation_ == LogicalOperation::And) {
		return left_b && right_b;
	} else {
		return left_b || right_b;
	}
}
