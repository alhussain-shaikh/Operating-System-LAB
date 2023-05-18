// C++ implementation of the Priority Based(Non-Preemptive) algorithm
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;
class process {
public:
	pid_t p_no = 0;
	time_t start_AT = 0, AT = 0,
		BT_left = 0, BT = 0, temp_BT = 0,
		CT = 0, TAT = 0, WT = 0, RT = 0;
	int priority = 0;

	// Function for completion time
	void set_CT(time_t time)
	{
		CT = time;
		set_TAT();
		set_WT();
	}

	// Function for Turn Around Time
	void set_TAT()
	{
		TAT = CT - start_AT;
	}

	// Function for Waiting Time
	void set_WT()
	{
		WT = TAT - BT;
	}
	void P_set()
	{
		start_AT = AT;
		BT_left = BT;
	}
	void set_RT(time_t time)
	{
		RT = time - start_AT;
	}

	// Overload operator '<' w.r.t arrival
	// time because arrival time is the
	// first priority even greater than
	// priority of process and priority_queue
	// pops out the greatest value first
	// so we need to replace '<' with '>' inorder
	// to pop out smallest value
	friend bool operator<(const process& a, const process& b)
	{
		return a.AT > b.AT;
	}
};

// Function to implement pop_index()
process pop_index(priority_queue<process>* main_queue,
				int index)
{
	priority_queue<process> rm_index;
	int i;
	process p;

	switch (index) {
	case 0:
		p = (*main_queue).top();
		(*main_queue).pop();
		break;
	default:
		for (i = 0; i < index; i++) {
			rm_index.push((*main_queue).top());
			(*main_queue).pop();
		}
		p = (*main_queue).top();
		(*main_queue).pop();

		while (!(*main_queue).empty()) {
			rm_index.push((*main_queue).top());
			(*main_queue).pop();
		}
		(*main_queue) = rm_index;
		break;
	}
	return p;
}

//Function to implement maximum priority w.r.t clock limit
// and 3rd parameter as bool because we need true = highest
//number as highest and false as lowest number as highest priority
int max_priority(priority_queue<process> main_priority_queue,
				int limit, bool high)
{
	int max = -1;
	if (high == 1) {
		while (!main_priority_queue.empty()
			&& main_priority_queue.top().AT <= limit) {
			if (main_priority_queue.top().priority > max)
				max = main_priority_queue.top().priority;
			main_priority_queue.pop();
		}
	}
	else {
		while (!main_priority_queue.empty()
			&& main_priority_queue.top().AT <= limit) {
			if (max == -1 || main_priority_queue.top().priority < max)
				max = main_priority_queue.top().priority;
			main_priority_queue.pop();
		}
	}
	return max;
}

// Function to implement maximum priority index
int max_priority_index(priority_queue<process> main_queue, int limit, bool high)
{
	int max = -1, i = 0, index = 0;
	if (high == 1) {
		while (!main_queue.empty() && main_queue.top().AT <= limit) {
			if (main_queue.top().priority > max) {
				max = main_queue.top().priority;
				index = i;
			}
			main_queue.pop();
			i++;
		}
	}
	else {
		while (!main_queue.empty()
			&& main_queue.top().AT <= limit) {
			if (max == -1 || main_queue.top().priority < max) {
				max = main_queue.top().priority;
				index = i;
			}
			main_queue.pop();
			i++;
		}
	}
	return index;
}

// Function to implement priority based Preemptive scheduling
priority_queue<process> Priority_NP_run(priority_queue<process> ready_queue,
										queue<process>* gantt, bool high)
{
	priority_queue<process> completion_queue;
	process p;
	time_t clock = 0;
	if (high == 1) {
		while (!ready_queue.empty()) {
			while (clock < ready_queue.top().AT) {
				p.temp_BT++;
				clock++;
			}
			if (p.temp_BT > 0) {
				p.p_no = -1;
				p.CT = clock;
				(*gantt).push(p);
			}
			p = pop_index(&ready_queue,
						max_priority_index(ready_queue,
											clock, high));
			p.set_RT(clock);

			while (p.BT_left > 0) {
				p.temp_BT++;
				p.BT_left--;
				clock++;
			}
			p.set_CT(clock);
			(*gantt).push(p);
			p.temp_BT = 0;

			completion_queue.push(p);
		}
	}
	else {
		while (!ready_queue.empty()) {
			while (clock < ready_queue.top().AT) {
				p.temp_BT++;
				clock++;
			}
			if (p.temp_BT > 0) {
				p.p_no = -1;
				p.CT = clock;
				(*gantt).push(p);
			}
			p = pop_index(&ready_queue,
						max_priority_index(ready_queue,
											clock, high));
			p.set_RT(clock);

			while (p.BT_left > 0) {
				p.temp_BT++;
				p.BT_left--;
				clock++;
			}
			p.set_CT(clock);
			(*gantt).push(p);
			p.temp_BT = 0;

			completion_queue.push(p);
		}
	}
	return completion_queue;
}

// Set data on the basis of given table
priority_queue<process> set_sample_data()
{
	priority_queue<process> ready_queue;
	process temp;
	int a;
	printf("Enter the No of processes: ");
	scanf("%d",&a);
	for(int i=0;i<a;i++){
	    printf("Enter the Process No : ");
	    scanf("%d",&temp.p_no);
	    printf("Enter the Arrival time of %d Process: ",i+1);
	    scanf("%ld",&temp.AT);
	    printf("Enter the Burst time of %d Process: ",i+1);
	    scanf("%ld",&temp.BT);
	    printf("Enter the Priority(High Value High Priority) of %d Process: ",i+1);
	    scanf("%d",&temp.priority);
	    temp.P_set();
	    ready_queue.push(temp);
	    printf("\n");
	}

	return ready_queue;
}

// Function to get total Waiting Time
double get_total_WT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().WT;
		processes.pop();
	}
	return total;
}

// Function to get total Turn Around Time
double get_total_TAT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().TAT;
		processes.pop();
	}
	return total;
}

// Function to get total Completion Time
double get_total_CT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().CT;
		processes.pop();
	}
	return total;
}

// Function to get total Response Time
double get_total_RT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().RT;
		processes.pop();
	}
	return total;
}

// Function to display main queue
void disp(priority_queue<process> main_queue, bool high)
{
	int i = 0, temp, size = main_queue.size();
	priority_queue<process> tempq = main_queue;
	double temp1;
	cout << "+-------------+--------------";
	cout << "+------------+-----------------";
	cout << "+-----------------+--------------+----------+";
	if (high == true)
		cout << " " << endl;
	else
		cout << endl;
	cout << "| Process No. | Arrival Time ";
	cout << "| Burst Time | Completion Time ";
	cout << "| Turnaround Time | Waiting Time |";
	if (high == true)
		cout << " Priority |" << endl;
	else
		cout << endl;
	cout << "+-------------+--------------";
	cout << "+------------+-----------------";
	cout << "+-----------------+--------------+----------+";
	if (high == true)
		cout << " " << endl;
	else
		cout << endl;
	while (!main_queue.empty()) {
		temp = to_string(main_queue.top().p_no).length();
		cout << '|' << string(6 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().p_no << string(7 - temp / 2, ' ');
		temp = to_string(main_queue.top().start_AT).length();
		cout << '|' << string(7 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().start_AT << string(7 - temp / 2, ' ');
		temp = to_string(main_queue.top().BT).length();
		cout << '|' << string(6 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().BT << string(6 - temp / 2, ' ');
		temp = to_string(main_queue.top().CT).length();
		cout << '|' << string(8 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().CT << string(9 - temp / 2, ' ');
		temp = to_string(main_queue.top().TAT).length();
		cout << '|' << string(8 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().TAT << string(9 - temp / 2, ' ');
		temp = to_string(main_queue.top().WT).length();
		cout << '|' << string(7 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().WT << string(7 - temp / 2, ' ');
		temp = to_string(main_queue.top().RT).length();
	    temp = to_string(main_queue.top().priority).length();
		
		if (high == true) {
			temp = to_string(main_queue.top().priority).length();
			cout << '|' << string(5 - temp / 2 - temp % 2, ' ')
				<< main_queue.top().priority << string(5 - temp / 2, ' ');
		}
		cout << "|\n";
		main_queue.pop();
	}
	cout << "+-------------+--------------";
	cout << "+------------+-----------------";
	cout << "+-----------------+--------------+----------+";
	if (high == true)
		cout << " ";
	cout << endl;

}

// Function to display Gantt Chart
void disp_gantt_chart(queue<process> gantt)
{
	int temp, prev = 0;
	queue<process> spaces = gantt;
	cout << "\n\nGantt Chart  :- \n\n+";
	while (!spaces.empty()) {
		cout << string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT, '-') << "+";
		spaces.pop();
	}
	cout << "\n|";
	spaces = gantt;
	while (!spaces.empty()) {
		cout << string(spaces.front().temp_BT, ' ');
		if (spaces.front().p_no == -1)
			cout << "IS" << string(spaces.front().temp_BT, ' ') << '|';
		else
			cout << "P" << spaces.front().p_no
				<< string(spaces.front().temp_BT, ' ') << '|';
		spaces.pop();
	}
	spaces = gantt;
	cout << "\n+";
	while (!spaces.empty()) {
		cout << string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT, '-')
			<< "+";
		spaces.pop();
	}
	spaces = gantt;
	cout << "\n0";
	while (!spaces.empty()) {
		temp = to_string(spaces.front().CT).length();
		cout << string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT - temp / 2 - prev, ' ')
			<< spaces.front().CT;
		prev = temp / 2 - temp % 2 == 0;
		spaces.pop();
	}
	cout << "\n\n";
}

// Driver Code
int main()
{
	// Initialise Ready and Completion Queue
	priority_queue<process> ready_queue, completion_queue;

	// queue for Gantt Chart
	queue<process> gantt;
	ready_queue = set_sample_data();

	// Function call to find completion data
//and true is passed as 3rd argument because we
//are considering highest number as highest priority
	completion_queue = Priority_NP_run(ready_queue, &gantt, true);

	// Display Completion Queue
	disp(completion_queue, true);

	// Display Gantt Chart
	disp_gantt_chart(gantt);
	return 0;
}



