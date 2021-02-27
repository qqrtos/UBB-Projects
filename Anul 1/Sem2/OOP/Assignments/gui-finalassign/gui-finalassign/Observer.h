#pragma once
#include <vector>

class Observer {
public:
	virtual void update() = 0;

	virtual ~Observer() = default;
};

class Subject {
private:
	std::vector<Observer*> observers;

public:
	Subject() = default;

	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void removeObserver(Observer* obs) {
		auto indx = std::find(observers.begin(), observers.end(), obs);
		if (indx != observers.end()) {
			observers.erase(indx);
		}
	}

	void notify() {
		for (auto each : this->observers) {
			each->update();
		}
	}

	~Subject() = default;
};