#pragma once
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <deque>
#include <mutex>

enum trivia_state_t
{
        TRIV_ASK_QUESTION = 1,
        TRIV_FIRST_HINT = 2,
        TRIV_SECOND_HINT = 3,
        TRIV_TIME_UP = 4,
        TRIV_ANSWER_CORRECT = 5,
        TRIV_END = 6
};


class in_msg
{
 public:
	std::string msg;
	int64_t author_id;
	bool mentions_bot;
	in_msg(const std::string &m, int64_t author, bool mention);
};

class state_t
{
	class TriviaModule* creator;
 public:
	std::mutex queuemutex;
	std::deque<in_msg> messagequeue;
	std::deque<in_msg> to_process;
	bool terminating;
	uint64_t channel_id;
	uint64_t guild_id;
	uint32_t numquestions;
	uint32_t round;
	uint32_t score;
	time_t start_time;
	std::vector<std::string> shuffle_list;
	trivia_state_t gamestate;
	int64_t curr_qid;
	time_t recordtime;
	std::string curr_question;
	std::string curr_answer;
	std::string curr_customhint1;
	std::string curr_customhint2;
	std::string curr_category;
	std::string shuffle1;
	std::string shuffle2;
	time_t curr_lastasked;
	time_t curr_recordtime;
	std::string curr_lastcorrect;
	int64_t last_to_answer;
	uint32_t streak;
	time_t asktime;
	bool found;
	time_t interval;
	uint32_t insane_num;
	uint32_t insane_left;
	uint32_t curr_timesasked;
	time_t next_quickfire;
	std::map<std::string, bool> insane;
	std::mutex timer_mutex;
	std::thread* timer;

	state_t(class TriviaModule* _creator);
	~state_t();
	void tick();
	void queue_message(const std::string &message, int64_t author_id, bool mentions_bot = false);
	void handle_message(const in_msg& m);
};

