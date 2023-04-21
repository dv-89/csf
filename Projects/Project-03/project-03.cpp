/*

Design and implement a request server that accepts requests. 
Each request that comes in has a randomly generated priority, 1 being the highest, and 5 being the lowest, 
and a randomly generated time-to-process between 1 and 5 seconds. 
The server can only process one request at a time. 
All requests are generated before the server can start processing them.

The program should support multiple servers!

Example output:

Enter number of requests: 10
Enter number of servers: 3
Enter maximum processing time per request: 5
Received request 1(5,4) // 1 = request id, 5 = priority, 4 = time to process
Server 0 added 1(5,4)
Server 0 requests: 1(5,4),
Received request 2(1,3)
Server 1 added 2(1,3)
Server 1 requests: 2(1,3),
Received request 3(5,5)
Server 2 added 3(5,5)
Server 2 requests: 3(5,5),
Received request 4(2,1)
Server 0 added 4(2,1)
Server 0 requests: 4(2,1),1(5,4),
Received request 5(2,3)
Server 1 added 5(2,3)
Server 1 requests: 2(1,3),5(2,3),
Received request 6(1,2)
Server 2 added 6(1,2)
Server 2 requests: 6(1,2),3(5,5),
Received request 7(5,1)
Server 0 added 7(5,1)
Server 0 requests: 4(2,1),7(5,1),1(5,4),
Received request 8(3,5)
Server 1 added 8(3,5)
Server 1 requests: 2(1,3),5(2,3),8(3,5),
Received request 9(3,2)
Server 2 added 9(3,2)
Server 2 requests: 6(1,2),9(3,2),3(5,5),
Received request 10(1,3)
Server 0 added 10(1,3)
Server 0 requests: 10(1,3),4(2,1),7(5,1),1(5,4),
Server 1 processing request 2(1,3)
Server 0 processing request 10(1,3)
Server 2 processing request 6(1,2)
Server 2 processing request 9(3,2)
Server 1 processing request 5(2,3)
Server 0 processing request 4(2,1)
Server 0 processing request 7(5,1)
Server 2 processing request 3(5,5)
Server 0 processing request 1(5,4)
Server 1 processing request 8(3,5)
Elapsed time: 11 seconds

*/
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <mutex>

using namespace std;

class mRequest{
    public:
    int request_id;
    int priority;
    int time_to_process;

    mRequest(int id, int p, int ttp){
        this->request_id = id;
        this->priority = p;
        this->time_to_process = ttp;
    }
};

bool compareByPriority(const mRequest& req1, const mRequest& req2) {
    return req1.priority < req2.priority;
}

void processRequest(int thread_id, vector<mRequest>& requestList, mutex& mtx) {
    while (true) {
        // lock the mutex to access the critical section
        mtx.lock();

        // check if the request list is empty
        if (requestList.empty()) {
            // release the mutex and break the loop
            mtx.unlock();
            break;
        }

        // remove the first request from the vector
        mRequest req = requestList.front();
        requestList.erase(requestList.begin());

        // release the mutex before processing the request
        mtx.unlock();

        // process the request
        cout << "Server " << thread_id << endl;
        cout << "processing Request with id " << req.request_id << " with priority " << req.priority << " and time to process " << req.time_to_process << " sec"<< "\n";
        this_thread::sleep_for(chrono::seconds(req.time_to_process));
        cout << endl << "completed : " << endl;
        cout << "Request " << req.request_id << " processed in " << req.time_to_process << " seconds by server" << thread_id << endl;
    }
}


int main(){
    int no_of_servers, no_of_requests, max_processing_time;

    cout << "Enter no of requests = ";
    cin >> no_of_requests;
    cout << endl << "Enter no of servers = ";
    cin >> no_of_servers;
    cout << endl << "Enter max processing time = ";
    cin >> max_processing_time;
    cout << endl;

    srand(time(NULL));
    //generate requests and add them to list and sort them based on priority.
    vector<mRequest> requestList; // priority based.
    for(int i=1; i<= no_of_requests; i++){
        int r_id = i;
        int r_p = rand() % 5 + 1;
        int r_ttp = rand() % max_processing_time + 1;
        mRequest new_request(r_id, r_p, r_ttp);
        requestList.push_back(new_request);
    }



    // cout << "Before sort: " << endl;
    // for (const auto& req : requestList) {
    //     std::cout << "Request " << req.request_id << " has priority " << req.priority << " and time to process " << req.time_to_process << "\n";
    // }

    // sort the vector based on priority
    std::sort(requestList.begin(), requestList.end(), compareByPriority);

  cout << "Priority 1 is high and 5 is low." << endl;

    cout << endl << "Requests sorted by priority: " << endl;
    // print the sorted vector
    for (const auto& req : requestList) {
        std::cout << "Request " << req.request_id << " has priority " << req.priority << " and time to process " << req.time_to_process << "\n";
    }

    
    // create a vector of threads
    //vector<thread> threadList;
    mutex mtx;
    vector<thread> threadList(no_of_servers);
    vector<vector<mRequest>> server_requests(no_of_servers);

    for (int i = 0; i < requestList.size(); i++) {
        int server_idx = i % no_of_servers;
        server_requests[server_idx].push_back(requestList[i]);
    }

    cout << endl << "Waitlist for each server : " << endl;
    for (const auto& server : server_requests) {
        for (const auto& request : server) {
            std::cout << "Server " << &server - &server_requests[0] << ": ";
            std::cout << "ID=" << request.request_id << std::endl;
        }
        cout << endl;
    }

    auto startTime = std::chrono::steady_clock::now();
    

    while (!requestList.empty()) {

        // for (int i = 0; i < no_of_servers && i < requestList.size(); i++) {
        //    threadList.emplace_back(processRequest, i, ref(requestList), ref(mtx));
        // }

        for (int i = 0; i < no_of_servers && i < requestList.size(); i++) {
           threadList.emplace_back(processRequest, i, ref(server_requests[i]), ref(mtx));
        }


        for (auto& t : threadList) {
        if (t.joinable()) {
            t.join();
        }
    }

        threadList.clear();

        requestList.erase(requestList.begin(), requestList.begin() + min(no_of_servers, static_cast<int>(requestList.size())));
    }
    
    auto endTime = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();


    std::cout << "Total execution time: " << totalTime << " sec" << std::endl;


    cout << "All requests processed." << endl;

    return 0;
    
}