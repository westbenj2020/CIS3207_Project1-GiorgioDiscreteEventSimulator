#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <queue>
#include <thread>
#include <chrono>
#include "project1.h"

#define SIMULATION_STARTED 0
#define JOB_ARRIVED 1
#define JOB_ENDED 2
#define JOB_TERMINATED 3
#define DISK1_STARTED 4
#define DISK1_FINISHED 5
#define CPU_STARTED 6
#define CPU_FINISHED 7
#define SIMULATION_ENDED 8
#define DISK2_STARTED 9
#define DISK2_FINISHED 10
#define NETWORK_STARTED 11
#define NETWORK_FINISHED 12


using namespace std;

int eventIDAllocationCounter = 1;
int jobIDAllocationCounter = 0;

class System  {

private:

    vector<Job> jobs;
    int arriveMin;
    int arriveMax;
    int quitProb;
    int networkProb;
    int initTime;
    int finTime;
    int currentTime;

public:

    const vector<Job> &getJobs() const {
        return jobs;
    }

    void setJobs(const vector<Job> &jobs) {
        System::jobs = jobs;
    }

    int getQuitProb() const {
        return quitProb;
    }

    void setQuitProb(int quitProb) {
        System::quitProb = quitProb;
    }

    int getNetworkProb() const {
        return networkProb;
    }

    void setNetworkProb(int networkProb) {
        System::networkProb = networkProb;
    }

    int getInitTime() const {
        return initTime;
    }

    void setInitTime(int initTime) {
        System::initTime = initTime;
    }

    int getFinTime() const {
        return finTime;
    }

    void setFinTime(int finTime) {
        System::finTime = finTime;
    }

    int getArriveMin() const {
        return arriveMin;
    }

    void setArriveMin(int arriveMin) {
        System::arriveMin = arriveMin;
    }

    int getArriveMax() const {
        return arriveMax;
    }

    void setArriveMax(int arriveMax) {
        System::arriveMax = arriveMax;
    }

    int getCurrentTime() const {
        return currentTime;
    }

    void setCurrentTime(int currentTime) {
        System::currentTime = currentTime;
    }

    /**priority_queue<Event> getSystemQueue() {
        return systemQueue;
    }**/

    /**void setSystemQueue(const priority_queue<Event> &systemQueue) {
        System::systemQueue = systemQueue;
    }**/

};

class DeviceDriver {

private:

    bool free;
    int deviceDriverMin;
    int deviceDriverMax;

public:

    bool isFree() const {
        return free;
    }

    void setFree(bool free) {
        DeviceDriver::free = free;
    }

    int getDeviceDriverMin() const {
        return deviceDriverMin;
    }

    void setDeviceDriverMin(int deviceDriverMin) {
        DeviceDriver::deviceDriverMin = deviceDriverMin;
    }

    int getDeviceDriverMax() const {
        return deviceDriverMax;
    }

    void setDeviceDriverMax(int deviceDriverMax) {
        DeviceDriver::deviceDriverMax = deviceDriverMax;
    }

};

class CPU {

private:

    bool free;
    int cpuMin;
    int cpuMax;

public:

    bool isFree() const {
        return free;
    }

    void setFree(bool free) {
        CPU::free = free;
    }

    int getCpuMin() const {
        return cpuMin;
    }

    void setCpuMin(int cpuMin) {
        CPU::cpuMin = cpuMin;
    }

    int getCpuMax() const {
        return cpuMax;
    }

    void setCpuMax(int cpuMax) {
        CPU::cpuMax = cpuMax;
    }

    void dequeue() {

    }

};

class Job {

private:

    int type;
    int id;
    int arriveMin;
    int arriveMax;
    int quitProb;
    int networkProb;
    int time;

public:

    Job(System system, int type) {
        this->setArriveMin(system.getArriveMin());
        this->setArriveMax(system.getArriveMax());
        this->setQuitProb(system.getQuitProb());
        this->setNetworkProb(system.getNetworkProb());
        this->setTime(); //using RNG mechanism
        this->type = type;
        this->setId(jobIDAllocationCounter); // unique id allocation
        jobIDAllocationCounter++;
    }

    Job(System system, int type, int time) {
        this->setArriveMin(system.getArriveMin());
        this->setArriveMax(system.getArriveMax());
        this->setQuitProb(system.getQuitProb());
        this->setNetworkProb(system.getNetworkProb());
        this->time = time; //using RNG mechanism
        this->type = type;
        this->setId(jobIDAllocationCounter); // unique id allocation
        jobIDAllocationCounter++;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    void setNetworkProb(int networkProb) {
        Job::networkProb = networkProb;
    }

    void setQuitProb(int quitProb) {
        Job::quitProb = quitProb;
    }

    int getArriveMin() const {
        return arriveMin;
    }

    void setArriveMin(int arriveMin) {
        Job::arriveMin = arriveMin;
    }

    int getArriveMax() const {
        return arriveMax;
    }

    void setArriveMax(int arriveMax) {
        Job::arriveMax = arriveMax;
    }

    double getQuitProb() const {
        return quitProb;
    }

    double getNetworkProb() const {
        return networkProb;
    }

    int getTime() const {
        return time;
    }

    void setTime() {
        int randNum = rand() % (this->getArriveMax() - this->getArriveMin() + 1) + this->getArriveMin();
        this->time = randNum;
    }

    void setTime(int time) {
        this->time = time;
    }

    int getType() const {
        return type;
    }

    void setType(int type) {
        this->type = type;
    }

    string getStrType() const {
        string eventType;
        switch (this->getType()) {
            case 0:
                eventType = "SIMULATION_STARTED";
                break;
            case 1:
                eventType = "JOB_ARRIVED";
                break;
            case 2:
                eventType = "JOB_ENDED";
                break;
            case 3:
                eventType = "JOB_TERMINATED";
                break;
            case 4:
                eventType = "DISK1_STARTED";
                break;
            case 5:
                eventType = "DISK1_FINISHED";
                break;
            case 6:
                eventType = "CPU_STARTED";
                break;
            case 7:
                eventType = "CPU_FINISHED";
                break;
            case 8:
                eventType = "SIMULATION_ENDED";
                break;
            case 9:
                eventType = "DISK2_STARTED";
                break;
            case 10:
                eventType = "DISK2_FINISHED";
                break;
            case 11:
                eventType = "NETWORK_STARTED";
                break;
            case 12:
                eventType = "NETWORK_FINISHED";
                break;
        }
        return eventType;
    }
};

/**class Event {
private:
    Job job = Job(System());
    int type;
    int id;
    string description;
    int time;
public:
    Event(System system, int eventType) { // this constructor is for events that dont require a correlative job
        // create event-handler in constructor
        this->setType(eventType);
        this->setId(eventIDAllocationCounter); // constructor increments counter variable to provide unique id allocation
        eventIDAllocationCounter++;
        this->setTime(system,system.getCurrentTime());
        this->setDescription(system);
    }
    Event(System system, int eventType, Job job) { // this constructor is for events that have a job
        // create event-handler in constructor
        this->setType(eventType);
        this->setId(eventIDAllocationCounter); // constructor increments counter variable to provide unique id allocation
        eventIDAllocationCounter++;
        this->setTime(system,system.getCurrentTime());
        this->setDescription(system,job);
    }
    const Job &getJob() const {
        return job;
    }
    void setJob(const Job &job) {
        Event::job = job;
    }
    int getTime() const {
        return time;
    }
    void setTime(System system, int time) {
        this->time = time;
    }
    void setTime(int time) {
        this->time = time;
    }
    int getType() const {
        return type;
    }
    void setType(int type) {
        this->type = type;
    }
    int getId() const {
        return id;
    }
    void setId(int id) {
        this->id = id;
    }
    const string &getDescription() const {
        return description;
    }
    void setDescription(System system) {
        string eventType;
        switch (this->getType()) {
            case 0:
                eventType = "SIMULATION_STARTED";
                break;
            case 1:
                eventType = "JOB_ARRIVED";
                break;
            case 2:
                eventType = "JOB_ENDED";
                break;
            case 3:
                eventType = "JOB_TERMINATED";
                break;
            case 4:
                eventType = "DISK1_STARTED";
                break;
            case 5:
                eventType = "DISK1_FINISHED";
                break;
            case 6:
                eventType = "CPU_STARTED";
                break;
            case 7:
                eventType = "CPU_FINISHED";
                break;
            case 8:
                eventType = "SIMULATION_ENDED";
                break;
            case 9:
                eventType = "DISK2_STARTED";
                break;
            case 10:
                eventType = "DISK2_FINISHED";
                break;
            case 11:
                eventType = "NETWORK_STARTED";
                break;
            case 12:
                eventType = "NETWORK_FINISHED";
                break;
        } //event type int to determine corresponding string
        this->description = "@time=" + to_string(system.getCurrentTime()) + ", Event " +
                to_string(this->getId()) + ": " + eventType;
    }
    void setDescription(System system, Job job) {
};**/

class cmpFunction {
public:
    int operator()(const Job &a, const Job &b) { // min-heap;
        return a.getTime() > b.getTime();
    }
};

int main() {

    srand(time(NULL));

    System Sys;
    CPU Cpu;
    DeviceDriver Disk1;
    DeviceDriver Disk2;
    DeviceDriver Network;

    // files for stats generation
    ofstream statFileCpuStart("statGenCpuStart.txt");
    ofstream statFileCpuFin("statGenCpuFin.txt");
    ofstream statFileJobArrive("statGenJobArrive.txt");
    ofstream statFileJobTerminated("statGenJobTerminated.txt");
    ofstream statFileDisk1Start("statGenDisk1Start.txt");
    ofstream statFileDisk1Fin("statGenDisk1Fin.txt");
    ofstream statFileDisk2Start("statGenDisk2Start.txt");
    ofstream statFileDisk2Fin("statGenDisk2Fin.txt");
    ofstream statFileNetworkStart("statGenNetworkStart.txt");
    ofstream statFileNetworkFin("statGenNetworkFin.txt");

    // file for LOG constants
    ofstream log("log.txt");
    ofstream stats("stats.txt");

    string line;
    vector<int> simValues;
    ifstream configFile;
    configFile.open("config.txt");
    if (!configFile) {
        cout << "\nUnable to open file.";
        exit(1);
    }
    while (getline(configFile, line)) {
        stringstream ss(line);
        for (int i; ss >> i;) {
            simValues.push_back(i);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        Sys.setInitTime(simValues[0]);
        Sys.setCurrentTime(simValues[0]);
        Sys.setFinTime(simValues[1]);
        Sys.setArriveMin(simValues[2]);
        Sys.setArriveMax(simValues[3]);
        Sys.setQuitProb(simValues[4]);
        Sys.setNetworkProb(simValues[5]);
        Cpu.setCpuMin(simValues[6]);
        Cpu.setCpuMax(simValues[7]);
        Disk1.setDeviceDriverMin(simValues[8]);
        Disk1.setDeviceDriverMax(simValues[9]);
        Disk2.setDeviceDriverMin(simValues[10]);
        Disk2.setDeviceDriverMax(simValues[11]);
        Network.setDeviceDriverMin(simValues[12]);
        Network.setDeviceDriverMax(simValues[13]);

        Cpu.setFree(true);
        Disk1.setFree(true);
        Disk2.setFree(true);
        Network.setFree(true);

        priority_queue<Job,vector<Job>,cmpFunction> systemQueue;
        queue<Job> CpuJobs;
        queue<Job> Disk1Jobs;
        queue<Job> Disk2Jobs;
        queue<Job> NetworkJobs;
        Job j(Sys,0,0); // simulation start event
        //cout << "@time:" + to_string(j.getTime()) + ", " + j.getStrType() + " - " + "Job " + to_string(j.getId());

        systemQueue.push(j);

        while (systemQueue.empty() == false) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (Cpu.isFree() == true && CpuJobs.empty() == false) {
                CpuJobs.front().setType(6);// change type of job at front of cpu queue to cpu started
                CpuJobs.front().setTime(CpuJobs.front().getTime());
                cout << "@time:" + to_string(Sys.getCurrentTime()) + ", " +
                        CpuJobs.front().getStrType() + " - " + "Job " +
                        to_string(CpuJobs.front().getId()) + "\n";
                log << "@time:" + to_string(Sys.getCurrentTime()) + ", " +
                        CpuJobs.front().getStrType() + " - " + "Job " +
                        to_string(CpuJobs.front().getId()) + "\n";
                statFileCpuStart << to_string(Sys.getCurrentTime()) + "," + CpuJobs.front().getStrType() + "," +
                to_string(CpuJobs.front().getId()) + "\n";
                CpuJobs.front().setType(7); // change job type to cpu fin
                CpuJobs.front().setTime(CpuJobs.front().getTime() +
                                        ((rand() % (Cpu.getCpuMax() - Cpu.getCpuMin() + 1) + Cpu.getCpuMin() +
                                          Sys.getCurrentTime())));
                systemQueue.push(CpuJobs.front()); // push job to system queue
                CpuJobs.pop(); // remove job from cpu queue
                Cpu.setFree(false);
            }
            if (Network.isFree() == true &&
                NetworkJobs.empty() == false) { // job can run now on network
                NetworkJobs.front().setType(
                        11);// change type of job at front of network queue to network started
                cout << "@time:" + to_string(NetworkJobs.front().getTime()) + ", " +
                        NetworkJobs.front().getStrType() + " - " + "Job " +
                        to_string(NetworkJobs.front().getId()) + "\n";
                log << "@time:" + to_string(NetworkJobs.front().getTime()) + ", " +
                        NetworkJobs.front().getStrType() + " - " + "Job " +
                        to_string(NetworkJobs.front().getId()) + "\n";
                statFileNetworkStart << to_string(systemQueue.top().getTime()) + "," +
                                    systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                NetworkJobs.front().setType(12); // change job type to network fin
                NetworkJobs.front().setTime(NetworkJobs.front().getTime() +
                                            ((rand() % (Network.getDeviceDriverMax() -
                                                        Network.getDeviceDriverMin() + 1) +
                                              Network.getDeviceDriverMin())));
                systemQueue.push(NetworkJobs.front()); // push job to system queue
                Network.setFree(false);
                //NetworkJobs.pop(); // remove job from cpu queue
            }
            if (Disk1.isFree() == true && Disk1Jobs.empty() == false) { // job can run now on disk1
                Disk1Jobs.front().setType(
                        4);// change type of job at front of disk1 queue to disk1 started
                cout << "@time:" + to_string(Disk1Jobs.front().getTime()) + ", " +
                        Disk1Jobs.front().getStrType() + " - " + "Job " +
                        to_string(Disk1Jobs.front().getId()) + "\n";
                log << "@time:" + to_string(Disk1Jobs.front().getTime()) + ", " +
                        Disk1Jobs.front().getStrType() + " - " + "Job " +
                        to_string(Disk1Jobs.front().getId()) + "\n";
                statFileDisk1Start << to_string(systemQueue.top().getTime()) + "," +
                                    systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                Disk1Jobs.front().setType(5); // change job type to disk1 fin
                Disk1Jobs.front().setTime(Disk1Jobs.front().getTime() +
                                          ((rand() % (Disk1.getDeviceDriverMax() -
                                                      Disk1.getDeviceDriverMin() + 1) +
                                            Disk1.getDeviceDriverMin())));
                systemQueue.push(Disk1Jobs.front()); // push job to system queue
                Disk1.setFree(false);
                //Disk1Jobs.pop(); // remove job from disk1 queue
            }
            if (Disk2.isFree() == true && Disk2Jobs.empty() == false) { // job can run now on disk2
                Disk2Jobs.front().setType(
                        9);// change type of job at front of disk2 queue to disk2 started
                cout << "@time:" + to_string(Disk2Jobs.front().getTime()) + ", " +
                        Disk2Jobs.front().getStrType() + " - " + "Job " +
                        to_string(Disk2Jobs.front().getId()) + "\n";
                log << "@time:" + to_string(Disk2Jobs.front().getTime()) + ", " +
                        Disk2Jobs.front().getStrType() + " - " + "Job " +
                        to_string(Disk2Jobs.front().getId()) + "\n";
                statFileDisk2Start << to_string(systemQueue.top().getTime()) + "," +
                                    systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                Disk2Jobs.front().setType(10); // change job type to disk2 fin
                Disk2Jobs.front().setTime(Disk2Jobs.front().getTime() +
                                          ((rand() % (Disk2.getDeviceDriverMax() -
                                                      Disk2.getDeviceDriverMin() + 1) +
                                            Disk2.getDeviceDriverMin())));
                systemQueue.push(Disk2Jobs.front()); // push job to system queue
                Disk2.setFree(false);
                //Disk2Jobs.pop(); // remove job from disk2 queue
            }
            //Event y = systemQueue.top(); // get Event at top of min-heap (Event with smallest Job time)
            if (systemQueue.top().getTime() >= Sys.getFinTime()) {
                cout << "@time:" + to_string(Sys.getCurrentTime()) + ", SIMULATION_FINISHED";
                log << "@time:" + to_string(Sys.getCurrentTime()) + ", SIMULATION_FINISHED";
                // close files
                statFileCpuStart.close();
                statFileCpuFin.close();
                statFileJobArrive.close();
                statFileJobTerminated.close();
                statFileDisk1Start.close();
                statFileDisk1Fin.close();
                statFileDisk2Start.close();
                statFileDisk2Fin.close();
                statFileNetworkStart.close();
                statFileNetworkFin.close();

                cout << "\n\nPrinting Program Statistics...";

                //create files to read job statistics from

                ifstream statsJobs;
                int jobCount = 0;
                statsJobs.open("statGenJobArrive.txt");
                if (!statsJobs) {
                    cout << "\nUnable to open jobs stats file.";
                    exit(1);
                }
                while (getline(statsJobs, line)) {
                    jobCount++;
                }
                cout << "\nThe system generated " + to_string(jobCount) + " jobs during this simulation.";
                stats << "\nThe system generated " + to_string(jobCount) + " jobs during this simulation.";



                ifstream statsCpuStart;
                int timesCpuStarted = -1; // -1 to account for erroneous first line of file
                statsCpuStart.open("statGenCpuStart.txt");
                if (!statsCpuStart) {
                    cout << "\nUnable to open CPU started stats file.";
                    exit(1);
                }
                while (getline(statsCpuStart, line)) {
                    timesCpuStarted++;
                }
                cout << "\nThe CPU started " + to_string(timesCpuStarted) + " times during this simulation.";
                stats << "\nThe CPU started " + to_string(timesCpuStarted) + " times during this simulation.";



                ifstream statsCpuFin;
                int timesCpuFinished = 0;
                statsCpuFin.open("statGenCpuFin.txt");
                if (!statsCpuFin) {
                    cout << "\nUnable to open CPU finished stats file.";
                    exit(1);
                }
                while (getline(statsCpuFin, line)) {
                    timesCpuFinished++;
                }
                cout << "\nThe CPU finished " + to_string(timesCpuFinished) + " times during this simulation.";
                stats << "\nThe CPU finished " + to_string(timesCpuFinished) + " times during this simulation.";


                ifstream statsNetworkStart;
                int timesNetworkStarted = 0;
                statsNetworkStart.open("statGenNetworkStart.txt");
                if (!statsNetworkStart) {
                    cout << "\nUnable to open network started stats file.";
                    exit(1);
                }
                while (getline(statsNetworkStart, line)) {
                    timesNetworkStarted++;
                }
                cout << "\nThe network started " + to_string(timesNetworkStarted) + " times during this simulation.";
                stats << "\nThe network started " + to_string(timesNetworkStarted) + " times during this simulation.";


                ifstream statsNetworkFin;
                int timesNetworkFinished = 0;
                statsNetworkFin.open("statGenNetworkFin.txt");
                if (!statsNetworkFin) {
                    cout << "\nUnable to open network finished stats file.";
                    exit(1);
                }
                while (getline(statsNetworkFin, line)) {
                    timesNetworkFinished++;
                }
                cout << "\nThe network finished " + to_string(timesNetworkFinished) + " times during this simulation.";
                stats << "\nThe network finished " + to_string(timesNetworkFinished) + " times during this simulation.";

                ifstream statsDisk1Start;
                int timesDisk1Started = 0;
                statsDisk1Start.open("statGenDisk1Start.txt");
                if (!statsDisk1Start) {
                    cout << "\nUnable to open disk1 started stats file.";
                    exit(1);
                }
                while (getline(statsDisk1Start, line)) {
                    timesDisk1Started++;
                }
                cout << "\nThe disk1 started " + to_string(timesDisk1Started) + " times during this simulation.";
                stats << "\nThe disk1 started " + to_string(timesDisk1Started) + " times during this simulation.";

                ifstream statsDisk1Fin;
                int timesDisk1Finished = 0;
                statsDisk1Fin.open("statGenDisk1Fin.txt");
                if (!statsDisk1Fin) {
                    cout << "\nUnable to open disk1 finished stats file.";
                    exit(1);
                }
                while (getline(statsDisk1Fin, line)) {
                    timesDisk1Finished++;
                }
                cout << "\nThe disk1 finished " + to_string(timesDisk1Finished) + " times during this simulation.";
                stats << "\nThe disk1 finished " + to_string(timesDisk1Finished) + " times during this simulation.";


                ifstream statsDisk2Start;
                int timesDisk2Started = 0;
                statsDisk2Start.open("statGenDisk2Start.txt");
                if (!statsDisk2Start) {
                    cout << "\nUnable to open disk2 started stats file.";
                    exit(1);
                }
                while (getline(statsDisk2Start, line)) {
                    timesDisk2Started++;
                }
                cout << "\nThe disk2 started " + to_string(timesDisk2Started) + " times during this simulation.";
                stats << "\nThe disk2 started " + to_string(timesDisk2Started) + " times during this simulation.";


                ifstream statsDisk2Fin;
                int timesDisk2Finished = 0;
                statsDisk2Fin.open("statGenDisk2Fin.txt");
                if (!statsDisk2Fin) {
                    cout << "\nUnable to open disk2 finished stats file.";
                    exit(1);
                }
                while (getline(statsDisk2Fin, line)) {
                    timesDisk2Finished++;
                }
                cout << "\nThe disk2 finished " + to_string(timesDisk2Finished) + " times during this simulation.";
                stats << "\nThe disk2 finished " + to_string(timesDisk2Finished) + " times during this simulation.";


                ifstream statsJobTermination;
                int timesJobTerminated = 0;
                statsJobTermination.open("statGenJobTerminated.txt");
                if (!statsJobTermination) {
                    cout << "\nUnable to open job termination stats file.";
                    exit(1);
                }
                while (getline(statsJobTermination, line)) {
                    timesJobTerminated++;
                }
                cout << "\n" + to_string(timesCpuStarted) + " jobs terminated during this simulation.\n";
                stats << "\n" + to_string(timesCpuStarted) + " jobs terminated during this simulation.\n";

                log << "\ninitTime: " + to_string(Sys.getInitTime()) + "\narriveMin: " + to_string(Sys.getArriveMin()) +
                "\narriveMax: " + to_string(Sys.getArriveMax()) + "\nquitProb: " + to_string(Sys.getQuitProb()/100.0) +
                "\nnetworkProb: " + to_string(Sys.getNetworkProb()/100.0) + "\ndisk1Prob: " +
                to_string((1.0-(Sys.getNetworkProb()/100.0))/2.0) + "\ndisk2Prob: " +
                to_string((1.0-(Sys.getNetworkProb()/100.0))/2.0);


                exit(0);
            }
            switch (systemQueue.top().getType()) {
                case 0: {// sim start event
                    cout << "@time:" + to_string(j.getTime()) + ", " +
                            j.getStrType() + " - " + "Job " + to_string(j.getId()) + "\n";
                    log << "@time:" + to_string(j.getTime()) + ", " +
                            j.getStrType() + " - " + "Job " + to_string(j.getId()) + "\n";
                    systemQueue.pop(); // if a sim start event, just pop and do nothing with the event
                    // we need to get it out of the way
                    Job x(Sys,1); // create job arrival event
                    systemQueue.push(x);
                    break;
                }
                case 1: {// job arrival event
                    Sys.setCurrentTime(systemQueue.top().getTime());
                    Job y(Sys,1);
                    y.setTime(y.getTime() + Sys.getCurrentTime());
                    systemQueue.push(y);
                    cout << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    log << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    statFileJobArrive << to_string(systemQueue.top().getTime()) + "," +
                                        systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                    CpuJobs.push(systemQueue.top()); // put job from job arrival event in cpu queue
                    //Sys.setCurrentTime(Sys.getCurrentTime() + systemQueue.top().getTime());
                    systemQueue.pop(); // pop job from priority queue

                    if (Cpu.isFree() == true && CpuJobs.empty() == false) {

                        CpuJobs.front().setType(6);// change type of job at front of cpu queue to cpu started
                        CpuJobs.front().setTime(CpuJobs.front().getTime());
                        cout << "@time:" + to_string(Sys.getCurrentTime()) + ", " +
                                CpuJobs.front().getStrType() + " - " + "Job " +
                                to_string(CpuJobs.front().getId()) + "\n";
                        log << "@time:" + to_string(Sys.getCurrentTime()) + ", " +
                                CpuJobs.front().getStrType() + " - " + "Job " +
                                to_string(CpuJobs.front().getId()) + "\n";
                        statFileCpuStart << to_string(systemQueue.top().getTime()) + "," +
                                            systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                        CpuJobs.front().setType(7); // change job type to cpu fin
                        CpuJobs.front().setTime(CpuJobs.front().getTime() +
                                                ((rand() % (Cpu.getCpuMax() - Cpu.getCpuMin() + 1) + Cpu.getCpuMin() +
                                                  Sys.getCurrentTime())));
                        systemQueue.push(CpuJobs.front()); // push job to system queue
                        CpuJobs.pop(); // remove job from cpu queue
                        Cpu.setFree(false);
                    }
                    break;
                }
                case 2: {// job ended; dont think I'm using this event type
                    break;
                }
                case 3: { // job terminated; not sure what to do with this event handler yet
                    break;
                }
                case 4: {
                    // disk 1 started
                    /**Disk1.setFree(false);
                    cout << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    Sys.setCurrentTime(Sys.getCurrentTime() + systemQueue.top().getTime()); //update sys time
                    // create new cpu fin event
                    systemQueue.pop();
                    x.setTime((rand() % (Disk1.getDeviceDriverMax() - Disk1.getDeviceDriverMin() + 1) +
                    Disk1.getDeviceDriverMin() + Sys.getCurrentTime())); // calc run time for cpu event to run
                    systemQueue.push(x); // push cpu fin event to system queue**/
                    break;
                }
                case 5: {
                    // disk 1 finished
                    Disk1.setFree(true);
                    cout << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    log << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    statFileDisk1Fin << to_string(systemQueue.top().getTime()) + "," +
                                        systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                    Sys.setCurrentTime(Sys.getCurrentTime() + systemQueue.top().getTime()); //update sys time
                    CpuJobs.push(Disk1Jobs.front());
                    Disk1Jobs.pop();
                    systemQueue.pop();
                    Job job(Sys,1);
                    job.setTime(Sys.getCurrentTime() + job.getTime());
                    systemQueue.push(job);
                    break;
                }
                case 6: { //cpu started event; use this only for jobs that are going back around the system
                    /**Cpu.setFree(false);
                    //cout << systemQueue.top().getDescription() + "\n"; // log event data
                    Event x(Sys,7,systemQueue.top().getJob()); // create new cpu fin event
                    systemQueue.pop(); // pop cpu started event from system queue
                    x.setTime((rand() % (Cpu.getCpuMax() - Cpu.getCpuMin() + 1) + Cpu.getCpuMin() +
                               Sys.getCurrentTime())); // calc run time for cpu event to run
                    systemQueue.push(x); // push cpu fin event to system queue
                    **/
                    break;
                }
                case 7: {
                    Cpu.setFree(true);
                    // cpu finished event
                    cout << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    log << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    statFileCpuFin << to_string(systemQueue.top().getTime()) + "," +
                                        systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                    Sys.setCurrentTime(systemQueue.top().getTime()); // increment system time
                    //systemQueue.pop(); // remove cpu fin event from system queue
                    float quitProb = float(float(Sys.getQuitProb()) / 100);
                    float networkProb = float(float(Sys.getNetworkProb()) / 100);
                    float disk1Prob = float(float((1 - networkProb)) / 2);
                    //cout << to_string(networkProb) + "  " + to_string(disk1Prob) + "\n";
                    float disk2Prob = networkProb - disk1Prob;
                    float quitOrContinueVal = float(rand()) / float(RAND_MAX);
                    if (quitOrContinueVal <= quitProb) {
                        cout << "@time:" + to_string(systemQueue.top().getTime()) + ", JOB_TERMINATED" + " - " + "Job "+
                                to_string(systemQueue.top().getId()) + "\n";
                        log << "@time:" + to_string(systemQueue.top().getTime()) + ", JOB_TERMINATED" + " - " + "Job "+
                                to_string(systemQueue.top().getId()) + "\n";
                        statFileJobTerminated << to_string(systemQueue.top().getTime()) + "," +
                                            systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                        systemQueue.pop();

                    } else {
                        // continue
                        float deviceDesignationVal = float(rand()) / float(RAND_MAX);
                        //cout << "\n" + to_string(deviceDesignationVal) + "\n";
                        if (deviceDesignationVal <= (networkProb)) { // network path
                            NetworkJobs.push(systemQueue.top()); // push network fin job to network queue
                            systemQueue.pop(); // pop network fin event from system queue
                            if (Network.isFree() == true &&
                                NetworkJobs.empty() == false) { // job can run now on network
                                NetworkJobs.front().setType(
                                        11);// change type of job at front of network queue to network started
                                cout << "@time:" + to_string(NetworkJobs.front().getTime()) + ", " +
                                        NetworkJobs.front().getStrType() + " - " + "Job " +
                                        to_string(NetworkJobs.front().getId()) + "\n";
                                log << "@time:" + to_string(NetworkJobs.front().getTime()) + ", " +
                                        NetworkJobs.front().getStrType() + " - " + "Job " +
                                        to_string(NetworkJobs.front().getId()) + "\n";
                                statFileNetworkStart << to_string(systemQueue.top().getTime()) + "," +
                                                    systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                                NetworkJobs.front().setType(12); // change job type to network fin
                                NetworkJobs.front().setTime(NetworkJobs.front().getTime() +
                                                            ((rand() % (Network.getDeviceDriverMax() -
                                                                        Network.getDeviceDriverMin() + 1) +
                                                              Network.getDeviceDriverMin())));
                                systemQueue.push(NetworkJobs.front()); // push job to system queue
                                Network.setFree(false);
                                //NetworkJobs.pop(); // remove job from cpu queue
                            }
                        }
                        if (deviceDesignationVal > networkProb && deviceDesignationVal <= (networkProb + disk1Prob)) {
                            // go to disk 1 event
                            Disk1Jobs.push(systemQueue.top()); // push cpu job to disk1 queue
                            systemQueue.pop(); // pop cpu fin event from system queue
                            if (Disk1.isFree() == true && Disk1Jobs.empty() == false) { // job can run now on disk1
                                Disk1Jobs.front().setType(
                                        4);// change type of job at front of disk1 queue to disk1 started
                                cout << "@time:" + to_string(Disk1Jobs.front().getTime()) + ", " +
                                        Disk1Jobs.front().getStrType() + " - " + "Job " +
                                        to_string(Disk1Jobs.front().getId()) + "\n";
                                log << "@time:" + to_string(Disk1Jobs.front().getTime()) + ", " +
                                        Disk1Jobs.front().getStrType() + " - " + "Job " +
                                        to_string(Disk1Jobs.front().getId()) + "\n";
                                statFileDisk1Start << to_string(systemQueue.top().getTime()) + "," +
                                                    systemQueue.top().getStrType() + "," +
                                                    to_string(systemQueue.top().getId()) + "\n";
                                Disk1Jobs.front().setType(5); // change job type to disk1 fin
                                Disk1Jobs.front().setTime(Disk1Jobs.front().getTime() +
                                                          ((rand() % (Disk1.getDeviceDriverMax() -
                                                                      Disk1.getDeviceDriverMin() + 1) +
                                                            Disk1.getDeviceDriverMin())));
                                systemQueue.push(Disk1Jobs.front()); // push job to system queue
                                Disk1.setFree(false);
                                //Disk1Jobs.pop(); // remove job from disk1 queue
                            }
                        }
                        else if (deviceDesignationVal <= 1.0) {
                            // go to disk 2 event
                            Disk2Jobs.push(systemQueue.top()); // push cpu fin job to disk2 queue
                            systemQueue.pop(); // pop disk2 fin event from system queue
                            if (Disk2.isFree() == true && Disk2Jobs.empty() == false) { // job can run now on disk2
                                Disk2Jobs.front().setType(
                                        9);// change type of job at front of disk2 queue to disk2 started
                                cout << "@time:" + to_string(Disk2Jobs.front().getTime()) + ", " +
                                        Disk2Jobs.front().getStrType() + " - " + "Job " +
                                        to_string(Disk2Jobs.front().getId()) + "\n";
                                log << "@time:" + to_string(Disk2Jobs.front().getTime()) + ", " +
                                        Disk2Jobs.front().getStrType() + " - " + "Job " +
                                        to_string(Disk2Jobs.front().getId()) + "\n";
                                statFileDisk2Start << to_string(systemQueue.top().getTime()) + "," +
                                                    systemQueue.top().getStrType() + "," +
                                                    to_string(systemQueue.top().getId()) + "\n";
                                Disk2Jobs.front().setType(10); // change job type to disk2 fin
                                Disk2Jobs.front().setTime(Disk2Jobs.front().getTime() +
                                                          ((rand() % (Disk2.getDeviceDriverMax() -
                                                                      Disk2.getDeviceDriverMin() + 1) +
                                                            Disk2.getDeviceDriverMin())));
                                systemQueue.push(Disk2Jobs.front()); // push job to system queue
                                Disk2.setFree(false);
                                //Disk2Jobs.pop(); // remove job from disk2 queue
                            }
                            if (Disk2.isFree() == false) {

                            }
                        }
                    }
                    break;
                }
                case 8: { // sim ended event

                }
                case 9: { // disk2 start event
                    /**Disk2.setFree(false);
                    //cout << systemQueue.top().getDescription() + "\n"; // log event data
                    Event x(Sys,10,systemQueue.top().getJob()); // create new disk2 fin event
                    systemQueue.pop(); // pop disk2 started event from system queue
                    x.setTime((rand() % (Disk2.getDeviceDriverMax() - Disk2.getDeviceDriverMin() + 1)
                               + Disk2.getDeviceDriverMin() + Sys.getCurrentTime())); // calc run time for disk2 event to run
                    systemQueue.push(x); // push disk2 fin event to system queue**/
                }
                case 10: { //disk2 ended event
                    Disk2.setFree(true);
                    cout << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    log << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    statFileDisk2Fin << to_string(systemQueue.top().getTime()) + "," +
                            systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                    Sys.setCurrentTime(Sys.getCurrentTime() + systemQueue.top().getTime()); //update sys time
                    CpuJobs.push(Disk2Jobs.front());
                    Disk2Jobs.pop();
                    systemQueue.pop();
                    Job job(Sys,1);
                    job.setTime(Sys.getCurrentTime() + job.getTime());
                    systemQueue.push(job);
                    break;
                }
                case 11: { //network start event
                    /**Network.setFree(false);
                    //cout << systemQueue.top().getDescription() + "\n"; // log event data
                    Event x(Sys,12,systemQueue.top().getJob()); // create new network fin event
                    systemQueue.pop(); // pop network started event from system queue
                    x.setTime((rand() % (Network.getDeviceDriverMax() - Network.getDeviceDriverMin() + 1)
                    + Network.getDeviceDriverMin() + Sys.getCurrentTime())); // calc run time for network event to run
                    systemQueue.push(x); // push network fin event to system queue**/
                }
                case 12: { //network ended event
                    Network.setFree(true);
                    cout << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    log << "@time:" + to_string(systemQueue.top().getTime()) + ", " +
                            systemQueue.top().getStrType() + " - " + "Job " +
                            to_string(systemQueue.top().getId()) + "\n";
                    statFileNetworkFin << to_string(systemQueue.top().getTime()) + "," +
                                        systemQueue.top().getStrType() + "," + to_string(systemQueue.top().getId()) + "\n";
                    Sys.setCurrentTime(Sys.getCurrentTime() + systemQueue.top().getTime()); //update sys time
                    CpuJobs.push(NetworkJobs.front());
                    NetworkJobs.pop();
                    systemQueue.pop();
                    Job job(Sys,1);
                    job.setTime(Sys.getCurrentTime() + job.getTime());
                    systemQueue.push(job);
                    break;
                }
            }
            //cout << "system queue size: " + to_string(systemQueue.size()) + "\n";
        }






        /**Sys.setCurrentTime(Sys.getCurrentTime() + y.getTime()); // increment sys time after process event
        systemQueue.pop(); // remove Event from top of min-heap (Event with smallest Job time)
        y.setType(6); // change type of event to reflect its new status
        y.setTime(Sys.getCurrentTime() + rand() % (Cpu.getCpuMax() - Cpu.getCpuMin() + 1) + Cpu.getCpuMin());
        y.setDescription(Sys,y.getJob());
        // ^^ the time that the new event will finish on the cpu
        cout << y.getDescription();**/
        // keep system running until finish time is reached.
        /**while (Sys.getFinTime() > Sys.getCurrentTime()) {
            Event x(Sys,1,Job(Sys)); // create a new job arrival event
            systemQueue.push(x); // push job arrival event to min-heap
            cout << x.getDescription();
            Event y = systemQueue.top(); // get Event at top of min-heap (Event with smallest Job time)
            Sys.setCurrentTime(Sys.getCurrentTime() + y.getTime()); // increment sys time after process event
            systemQueue.pop(); // remove Event from top of min-heap (Event with smallest Job time)
            if (Cpu.isFree()==true && Cpu.getCpuJobs().empty()==false) { // there is a job in cpu queue that can run on cpu
                // pop and return job at front of cpu queue
            }
        }**/

    }
    return 0;
}