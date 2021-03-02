#pragma once

#include "date.h"

#include <iostream>
#include <memory>


enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	Node(){}
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode(){}
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& comparison, const Date& date)
			: comparison_(comparison)
			, date_(date) {
	}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const Comparison comparison_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& comparison, const std::string& event)
			: comparison_(comparison)
			, event_(event) {
	}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const Comparison comparison_;
	const std::string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& logical_operation,
			const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right)
			: logical_operation_(logical_operation)
			, left_(left), right_(right){
	}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const LogicalOperation logical_operation_;
	const std::shared_ptr<Node> left_;
	const std::shared_ptr<Node> right_;
};
