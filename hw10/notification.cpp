#include "notification.h"
#include "user.h"

void create_notifications(std::string& events_file, User& user, 
std::queue<Notification*>& aggregates, std::queue<std::string>& outputs){
        if(user.get_pause_bool() == true){
            return;
        }
    	// assume inputFile is a std::string, containing the file name of the input file.
        std::ifstream jsonFile(events_file);
        if (!jsonFile.is_open()) {
                std::cerr << "Failed to open the JSON file." << std::endl;
                exit(1);
        }
        std::string name;
        std::string command;
        std::string third;
        while (jsonFile >> name) {
            jsonFile >> command;
            jsonFile >> third;
            //checks if the command given is one of the five possible
            //then checks if the third string given is either the correct user
            //or a post by the correct user
            //then checks if the user allows that type of notification
            //creates a derived notification class object if so     
            if(command == "likes" && (user.get_posts()).find(third)!= (user.get_posts()).end()
             && user.get_likes_bool() == true){
                Notification* notif_ptr = new Like;
                (*(notif_ptr)).set_name(name);
                (*(notif_ptr)).set_command(command);
                (*(notif_ptr)).set_third(third);
                add_notifications(notif_ptr, aggregates, outputs);
            }else if(command == "tags" && third == user.get_username()
             && user.get_tags_bool() == true){
                Notification* notif_ptr = new Tag;
                (*(notif_ptr)).set_name(name);
                (*(notif_ptr)).set_command(command);
                (*(notif_ptr)).set_third(third);
                add_notifications(notif_ptr, aggregates, outputs);
            }else if(command == "comments_on" && (user.get_posts()).find(third)!= (user.get_posts()).end() 
            && user.get_comments_bool() == true){
                Notification* notif_ptr = new Comment;
                (*(notif_ptr)).set_name(name);
                (*(notif_ptr)).set_command(command);
                (*(notif_ptr)).set_third(third);
                add_notifications(notif_ptr, aggregates, outputs);
            }else if(command == "follows" && third == user.get_username()
             && user.get_follows_bool() == true){
                Notification* notif_ptr = new Follow;
                (*(notif_ptr)).set_name(name);
                (*(notif_ptr)).set_command(command);
                (*(notif_ptr)).set_third(third);
                add_notifications(notif_ptr, aggregates, outputs);
            }else if(command == "messageRequests" && third == user.get_username() 
                && user.get_message_bool() == true){
                Notification* notif_ptr = new Message;
                (*(notif_ptr)).set_name(name);
                (*(notif_ptr)).set_command(command);
                (*(notif_ptr)).set_third(third);
                add_notifications(notif_ptr, aggregates, outputs);
            }
        }
        //checks if the aggregate is empty at the end of the run
        //if it is, checks if the size is > 3 
        //if so it aggregates them
        //if not it adds them to output
        if(!aggregates.empty()){
            if(aggregates.size() > 3){
                std::string action;
                if((*(aggregates.front())).get_command() == "likes"){
                    action = "liked your post.";
                }else if((*(aggregates.front())).get_command() == "tags"){
                    action = "tagged you in a post.";
                }else if((*(aggregates.front())).get_command() == "comments_on"){
                    action = "commented on your post.";
                }else if((*(aggregates.front())).get_command() == "follows"){
                    action = "started following you.";
                }else{
                    action = "wants to send you a message.";
                }
                //create a stack since the last 2 events are 
                //the two that are displayed in the output file
                std::stack<Notification*> ordered_agg;
                while(!aggregates.empty()){
                    ordered_agg.push(aggregates.front());
                    aggregates.pop();
                }
                std::string out_put;
                //create a string containting the top 2 elements names
                //and the size of the rest of the 
                out_put = ((*(ordered_agg.top()))).get_name();
                Notification* temp1 = ordered_agg.top();
                ordered_agg.pop();
                delete temp1;

                out_put += ", " + ((*(ordered_agg.top()))).get_name();
                Notification* temp2 = ordered_agg.top();
                ordered_agg.pop();
                delete temp2;
                out_put +=  " and " + std::to_string(ordered_agg.size())
                + " others " + action + "\n";
                if(outputs.size() >= 100){
                    outputs.pop();
                    outputs.push(out_put);
                }else{
                    outputs.push(out_put);
                }
                while(!ordered_agg.empty()){
                    Notification* temp3 = ordered_agg.top();
                    ordered_agg.pop();
                    delete temp3;
                }
            }else{
                while(!aggregates.empty()){
                    if(outputs.size() >= 100){
                        outputs.pop();
                        outputs.push(aggregates.front()->print());
                    }else{
                        outputs.push(aggregates.front()->print());
                    }
                    Notification* temp = aggregates.front();
                    aggregates.pop();
                    delete temp;
                }
            }
        }
        // don't need this json file anymore, as the content is read into json_content.
        jsonFile.close();
}

void add_notifications(Notification* notif_ptr,  std::queue<Notification*>& aggregates, std::queue<std::string>& outputs){
    //if aggregate queue is empty add the notification
    if(aggregates.empty()){
        aggregates.push((notif_ptr));
    }else{
        //if there are already notifications in the queue
        //check if notif is the same type of notification
        //if it is add it to the queue
        if((*(aggregates.front())).get_command() == (*(notif_ptr)).get_command()){
            aggregates.push((notif_ptr));
        }else{
            //if its not and the queue size is <= 3
            //print each notification on its own
            //increase count by queue size
            //clear the queue add notif
            if(aggregates.size() <= 3){
                while(!aggregates.empty()){
                    if(outputs.size() >= 100){
                        outputs.pop();
                        outputs.push(aggregates.front()->print());
                    }else{
                        outputs.push(aggregates.front()->print());
                    }
                    Notification* temp = aggregates.front();
                    aggregates.pop();
                    delete temp;
                }
                aggregates.push((notif_ptr));
            }else{
                //if the queue size is > 3
                //print the name of the last two notifs
                //in the queue, then the size of the queue is the
                //number of others that preformed the same action
                //clear the queue and add the notif
                std::string action;
                if((*(aggregates.front())).get_command() == "likes"){
                    action = "liked your post.";
                }else if((*(aggregates.front())).get_command() == "tags"){
                    action = "tagged you in a post.";
                }else if((*(aggregates.front())).get_command() == "comments_on"){
                    action = "commented on your post.";
                }else if((*(aggregates.front())).get_command() == "follows"){
                    action = "started following you.";
                }else{
                    action = "wants to send you a message.";
                }
                //create a stack since the last 2 events are 
                //the two that are displayed in the output file
                std::stack<Notification*> ordered_agg;
                while(!aggregates.empty()){
                    ordered_agg.push(aggregates.front());
                    aggregates.pop();
                }
                std::string out_put;
                //create a string containting the top 2 elements names
                //and the size of the rest of the 
                out_put = ((*(ordered_agg.top()))).get_name();
                Notification* temp1 = ordered_agg.top();
                ordered_agg.pop();
                delete temp1;

                out_put += ", " + ((*(ordered_agg.top()))).get_name();
                Notification* temp2 = ordered_agg.top();
                ordered_agg.pop();
                delete temp2;
                
                out_put +=  " and " + std::to_string(ordered_agg.size())
                + " others " + action + "\n";
                //checks if an item needs to be removed from the outputs
                //adds the new output
                if(outputs.size() >= 100){
                    outputs.pop();
                    outputs.push(out_put);
                }else{
                    outputs.push(out_put);
                }
                while(!ordered_agg.empty()){
                    Notification* temp3 = ordered_agg.top();
                    ordered_agg.pop();
                    delete temp3;
                }
                aggregates.push((notif_ptr));
            }
        }
    }
}
