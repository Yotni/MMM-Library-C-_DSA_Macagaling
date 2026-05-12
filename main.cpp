#include <iostream>
#include <string>
#include <vector>


using namespace std;
// For Personal
struct Personal_List{
    string ID;
    string Title;
    string Type_of_MMM;
    string Story_status;
    string Genre[39];
    int Genre_Counter;
    string rev_rec;
};

struct Personal_Node {
    Personal_List data;
    Personal_Node* next;
};

// for Public
struct Public_Section{
    string ID;
    string Title;
    string Type_of_MMM;
    string Story_status;
    string Genre[39];
    int Genre_Counter;
    vector<string> rev_rec;
};

struct Public_Node{
    Public_Section data;
    Public_Node* next;
};

// Beloe are my functions for my functions in my programmed, jsut for easy outputting and Case format:
// For lowering letters
string Lower(string L) {
    for (int i = 0; i < L.length(); i++){
        L[i] = tolower(L[i]);
    }
    return L;
}
// For uppercase letters
string Upper(string U) {
    for (int i = 0; i < U.length(); i++){
        U[i] = toupper(U[i]);
    }
    return U;
}
// For outputting genres in a good way po
void print_genre(string items[], int start, int last, int per_line) {
    int count = 0;

    for (int i = start; i < last; i++) {
        cout << "[" << items[i] << "] ";
        count ++;
        if (count % per_line == 0) {
            cout << endl;
        }
    }
}


// Below are my functions in my programmed: PS the sub functions doesnt need to be here, just that to know what are every functions created.
// Selections sections:
void main_menu(Personal_Node* Personal_head, Public_Node* Public_head);

// Personal list Functions:
void Display_Per_L(Personal_Node* Personal_head);
void Add_Story(Personal_Node*& Personal_head);
void Delete_Story(Personal_Node*& Personal_head);
void Share_Personal_list(Personal_Node* Personal_head, Public_Node*& Public_head);

// Sub-Functions for Personal List:
    // for adding
string CreateID_Personal(Personal_Node* Personal_head);
void Insert_Story_LinkL(Personal_Node*& Personal_head, Personal_List newdata);
bool If_Story_Title_Exist(Personal_Node* Personal_head,string Lower_C_Title);
    // for deleting
bool Is_PLL_Empty(Personal_Node* Personal_head);
bool Is_StoryID_Exist(Personal_Node* Personal_head,string id_maker);
struct Personal_Node* Find_ID_Title(Personal_Node* Personal_head, string id_maker);
void Delete_Story_LinkL(Personal_Node*& Personal_head, string id_maker);
void ReIndex_Story_ID(Personal_Node*& Personal_head);


// Public List Functions:
void Display_Pub_L(Public_Node* Public_head);
void Search_via_title(Public_Node* Public_head);
void View_By_Story_ID(Public_Node* Public_head);
void View_by_Type_Novel(Public_Node* Public_head);
void View_by_Story_Status(Public_Node* Public_head);

// this is for global keyword to exit;
string Keyword_to_cancel = "exit";


void Add_Sample_Data(Personal_Node*& Personal_head); //this is for sample only so that i know if title exist code and display function work
void Add_Sample_Data_Public(Public_Node*& Public_head); //this is for sample only so that i know if viewing work in public and rec and rev share only work



// the main ------>
int main() {
    // Just for inputting a story so that there is already existing story:
    Personal_Node* Personal_head = nullptr;
    Public_Node* Public_head = nullptr;
    Add_Sample_Data(Personal_head);
    Add_Sample_Data_Public(Public_head);
    main_menu(Personal_head, Public_head);
    return 0;
}


// Menu sections: Personal and Public
void main_menu(Personal_Node* Personal_head, Public_Node* Public_head){
    string section_choice;

    while (true) {
        cout << endl << string(100, '-') << endl;
        cout << "MMM_Library&Public List\n";
        cout << "1. Personal Library List\n";
        cout << "2. Public Lists\n";
        cout << "3. Press X to exit\n";
        cout << "Pick a section: ";
        cin >> section_choice;
        cin.ignore();

        if(section_choice == "1"){
            string PLL_Selection;
             while (true){
                cout << endl << string(100, '-') << endl;
                cout << "Welcome to Personal Library List: \n\n";
                cout << "1. Display your Personal Library List\n";
                cout << "2. Add a Story\n";
                cout << "3. Delete a story\n";
                cout << "4. Do your want to share a story\n";
                cout << "5. Hit X to go back to main menu\n";
                cout << "Do you want to display, add, delete, share or go back: ";
                cin >> PLL_Selection;

                if (PLL_Selection == "1"){
                    Display_Per_L(Personal_head);
                }
                else if (PLL_Selection == "2"){
                    Add_Story(Personal_head);
                }
                else if (PLL_Selection == "3"){
                    Delete_Story(Personal_head);
                }
                else if (PLL_Selection == "4"){
                    Share_Personal_list(Personal_head, Public_head);
                }
                else if(Lower(PLL_Selection) == "x"){
                    break;
                }
                else {
                    cout << "Invalid input" << endl;
                }
            }
        }
        else if(section_choice == "2"){
            string PUB_Selection;
            while(true){
                Display_Pub_L(Public_head);
                cout << endl << string(100, '-') << endl;
                cout << "1. Search a Title\n";
                cout << "2. Pick a Story to view using Story_ID\n";
                cout << "3. Do you want to view using specific Type of Graphic Novel?\n";
                cout << "4. Do you want to view using specific Type of Story Status\n";
                cout << "5. Hit X to go back to main menu\n";

                cout << "Remember: Enter Exit when inside section 1 to 4 to cancel viewing.\n";

                cout << "Do you want to search, view a story, view via graphic novel or via Story Status, or go back: ";
                getline(cin, PUB_Selection);

                if (PUB_Selection == "1"){
                    Search_via_title(Public_head);
                }
                else if (PUB_Selection == "2"){
                    View_By_Story_ID(Public_head);
                }
                else if (PUB_Selection == "3"){
                    View_by_Type_Novel(Public_head);
                }
                else if (PUB_Selection == "4"){
                    View_by_Story_Status(Public_head);
                }
                else if (Lower(PUB_Selection) == "x"){
                    break;
                }
                else {
                    cout << "Invalid input" << endl;
                }
            }
        }
        else if(section_choice == "X" || section_choice == "x"){
            break;
        }
        else {
            cout << "Invalid input" << endl;
        }

    };
}


// =======This is the functions in the Personal list po --------------------->
// for Displaing Linked Lists Stories for Personal:
void Display_Per_L(Personal_Node* Personal_head){
    Personal_Node* Temp_Display = Personal_head;

    cout << string(100, '-') << endl;
    cout << "Your List of stories:\n";

    if(Temp_Display == nullptr){
        cout << "Personal List is empty!\n";
        return;
    }

    while(Temp_Display != nullptr){
        cout << Temp_Display->data.ID <<":\n";
        cout << "\tTitle: " << Temp_Display->data.Title << endl;
        cout << "\tType of Graphic Novel: " << Temp_Display->data.Type_of_MMM << endl;
        cout << "\tStory Status: " << Temp_Display->data.Story_status << endl;
        
        for (int i = 0; i < Temp_Display->data.Genre_Counter; i++){
            if (Temp_Display->data.Genre[i] == Temp_Display->data.Genre[0]){
               cout << "\tGenres: ";
            }
            cout << Temp_Display->data.Genre[i];
            
            if (i < Temp_Display->data.Genre_Counter - 1) {
                cout << ", ";
            }
        }
        cout << endl;
        cout << "\tReview and reccomendations:\n" << "\t\t - " << Temp_Display->data.rev_rec << endl;

        Temp_Display = Temp_Display->next;
    }

    cout << string(100, '-') << endl;

    return;
}
// ------------------------weeeeh

// for adding a Story line of code and Functions:
string CreateID_Personal(Personal_Node* Personal_head){
    int Count_Story = 0;
    Personal_Node* temp = Personal_head;

    while (temp != nullptr){
        Count_Story ++;
        temp = temp->next;
    }

    string id_maker = "Story " + to_string(Count_Story + 1);

        
    return id_maker;

}

void Insert_Story_LinkL(Personal_Node*& Personal_head, Personal_List newdata){

    Personal_Node* newNode = new Personal_Node();
    newNode->data = newdata;
    newNode->next = nullptr;

    if (Personal_head == nullptr) {
        Personal_head = newNode;
        return;
    }

    Personal_Node* last = Personal_head;

    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = newNode;
}

bool If_Story_Title_Exist(Personal_Node* Personal_head,string Lower_C_Title){
    bool Title_exist = false;   
            Personal_Node * temp = Personal_head;

            while (temp != nullptr){
                if(Lower(temp->data.Title) == Lower_C_Title){
                    Title_exist = true;
                    break;
                }
                temp = temp->next;
            }

        return Title_exist;


}

void Add_Story(Personal_Node*& Personal_head){
    Personal_List Story;

    cin.ignore();
    cout << string(100, '-') << endl;
    cout << "Add a story:\n";
    cout << "Remember: Enter [Exit] at any time to cancel adding a new story.\n";
    while (true){
        // For inputting Title
        while (true){
            cout << "Title: ";
            getline(cin, Story.Title);
            string Lower_C_Title = Lower(Story.Title);
            // for cancellation
            if(Lower_C_Title == Keyword_to_cancel){
                cout << "Adding a Story was cancelled";
                return;
            }
            
            if (Story.Title == ""){
                cout << "You did'nt input any title\n";
                continue;
            }

            bool Title_exist = If_Story_Title_Exist(Personal_head, Lower_C_Title);
            
            if (Title_exist){
                cout << "The title " << Story.Title << " already exist in your library:\n";
            }
            else {
                Story.Title = Upper(Story.Title);
                break;
            }

        } 
        cout << "Story Information: " << endl;
        string Type_Graphic_Novels[3] = {"Manwha", "Manhua" , "Manga"};
        bool Valid_Type = false;

        // For inputting Graphic novel type:
        while (true){
            cout << "Type of Graphic Novel(Manwha/Manhua/Manga): ";
            getline(cin, Story.Type_of_MMM);
            string Lower_C_MMM = Lower(Story.Type_of_MMM);

            // for cancellation
            if(Lower_C_MMM == Keyword_to_cancel){
                cout << "Adding a Story was cancelled";
                return;
            }

            for (int i = 0; i < 3; i++) {
                if (Lower_C_MMM == Lower(Type_Graphic_Novels[i])){
                    Story.Type_of_MMM = Type_Graphic_Novels[i];
                    Valid_Type = true;
                }
            }
            if(Valid_Type){
                break;
            }
            else{
                cout << Story.Type_of_MMM << " is not in the graphic novel type.\n";
            }
        }

        // for inputting Story Status:

        string Story_Statuses[4] = {"Ongoing", "Completed", "Cancelled", "Hiatus"};
        bool Valid_Status = false;

        while (true){
            cout << "Story status, is it ongoing, completed, cancelled, or on hiatus: ";
            getline(cin, Story.Story_status);
            string Lower_C_Status = Lower(Story.Story_status);
            bool Valid_Status = false;

            // for cancellation
            if(Lower_C_Status == Keyword_to_cancel){
                cout << "Adding a Story was cancelled";
                return;
            }

            for (int i = 0; i < 4; i++){
                if (Lower_C_Status == Lower(Story_Statuses[i])){
                    Story.Story_status = Story_Statuses[i];
                    Valid_Status = true;
                }
            }
            if (Valid_Status){
                break;
            }
            else{
                cout << Story.Story_status << " is not in the story statuses\n";
            }
        }

        // for inputting Story Status:
        cout << "Pick Genres (input X to stop):\n";
        string Every_Genres[39]= {
                "Action", "Kingdom Building", "Adventure", "Comedy", "Crime", "Drama", "Fantasy", 
                "Gore", "Historical", "Horror", "Isekai", "Mature", "Mecha", "Medical", "Mystery", 
                "Romance", "Sci-Fi", "Slice of Life", "Sports", "Superhero", "Thriller", 
                "Apocalyptic", "Post-Apocalyptic", "Pre-Apocalyptic", "Cultivation","Murim", 
                "Dungeons", "Martial Arts", "Magic", "Noble", "Rebirth", "Regression", "Reincarnation",
                "Revenge", "Supernatural", "Survival", "Time Travel", "Tower", "Villain"
        };

        // 
        print_genre(Every_Genres, 0, 18, 9);   
        print_genre(Every_Genres, 18, 25, 7);
        print_genre(Every_Genres, 25, 39, 9);
        
        Story.Genre_Counter = 0;
        cout << endl << string(100, '-') << endl;
        cout << "Genres:\n";

        while(true){
            string Select_Genre;
            getline(cin, Select_Genre);

            string Lower_C_Genre = Lower(Select_Genre);

            bool Valid_Genre = false;

            // for cancellation
            if(Lower_C_Genre == Keyword_to_cancel){
                cout << "Adding a Story was cancelled";
                return;
            }

            if (Lower_C_Genre == "x") {
                break; // stop input
            }

            for(int i = 0; i < 39; i++){
                if(Lower_C_Genre == Lower(Every_Genres[i])){
                    Select_Genre = Every_Genres[i];
                    bool Already_added = false;

                for(int j = 0; j < 39; j++){
                    if(Select_Genre == Story.Genre[j]){
                        Already_added = true;
                        break;
                    }
                }
                if(Already_added){
                    cout << "Genre already added!\n";
                    Valid_Genre = true;
                    break;
                }
                else{
                    Valid_Genre = true;
                    Story.Genre[Story.Genre_Counter] = Select_Genre;
                    Story.Genre_Counter ++;
                    break;
                }
                }
            }

            if(!Valid_Genre){
                cout << "The genre " << Select_Genre << " is not in the Library!" << endl;
            }
        }

        // For inputting Review and recommendation:
        while(true){
            cout << "Review and recommendation: ";
            getline(cin, Story.rev_rec);

            // for cancellation
            if(Lower(Story.rev_rec) == Keyword_to_cancel){
                cout << "Adding a Story was cancelled";
                return;
            }

            if(Story.rev_rec == ""){
                cout << "Please put your review and recommendation about this story!\n";
            }
            else break;
        }


        // Linked list code for inputting struct Story
        string Add_ToList_Selection;
        while(true){
            cout << "Do you want to add " << Story.Title << " in your Personal List[Y/N]: ";
            getline(cin, Add_ToList_Selection);
            if (Lower(Add_ToList_Selection) == "y"){
                // For inputting Id(Story [num]):
                Story.ID =  CreateID_Personal(Personal_head);

                Insert_Story_LinkL(Personal_head, Story);
                cout << "The story was added succesfully!" << endl;
                break;
            }
            else if(Lower(Add_ToList_Selection) == "n"){
                cout << "Adding the story was cancelled!" << endl;
                break;
            }
            else{
                cout << "Invalic Input" << endl;
            }
        }

        // ask if want to add more:
        string Add_More_Selection;
        bool add_more = false;
        while(true){
            cout << "Do you want to add another Story[Y/N]: ";
            getline(cin, Add_More_Selection);
            if (Lower(Add_More_Selection) == "y"){
                add_more = true;
                break;
            }
            else if(Lower(Add_More_Selection) == "n"){
                return;
            }
            else{
                cout << "Invalid Input\n";
            }
        }
    }
    
}
// ------------------------weeeeh

// For deleting a Story line of code and Functions: 
bool Is_PLL_Empty(Personal_Node* Personal_head){
    Personal_Node* temp = Personal_head;

    if (temp == nullptr){
        cout << "Library is empty.\n";
        return true;
    }
    else{
        return false;
    }


}

bool Is_StoryID_Exist(Personal_Node* Personal_head,string id_maker){
    bool ID_exist = false;
    Personal_Node * temp = Personal_head;
    string temp_ID = id_maker;

    while (temp != nullptr){
        if(temp->data.ID == temp_ID){
            ID_exist = true;
                    break;
        }
        temp = temp->next;
    }
    if (ID_exist){
        return true;
    }
    else {
        cout << temp_ID << " is not in your Library\n";
        return false;
    }
}

struct Personal_Node* Find_ID_Title(Personal_Node* Personal_head, string id_maker){
    Personal_Node* temp = Personal_head;
    string temp_ID = id_maker;

    while (temp != nullptr){
        if (temp->data.ID == id_maker){
            break;
        }
        temp = temp->next;
    }

    return temp;
}

void Delete_Story_LinkL(Personal_Node*& Personal_head, string id_maker){
    Personal_Node* temp = Personal_head;
    Personal_Node* prev = nullptr;
    string temp_id_maker = id_maker;

        while(temp != nullptr ){
            if(temp->data.ID == id_maker){
                if(temp == Personal_head){
                    Personal_head = Personal_head->next;
                }
                else{
                    prev->next = temp->next;
                }
                delete temp;
            }
            prev = Personal_head;
            temp = temp->next;
        }
}

void ReIndex_Story_ID(Personal_Node*& Personal_head){
    int index_ID = 1;
    Personal_Node* temp = Personal_head;
    while(temp != nullptr){
        string ID_maker = "Story " + to_string(index_ID);
        temp->data.ID = ID_maker;
        temp = temp->next;
        index_ID ++;
    }

}

void Delete_Story(Personal_Node*& Personal_head){
    cin.ignore();
    string Story_Id, Story_Id_Maker, Delete_Selection;
    cout << string(100, '-') << endl;
    cout << "Delete a Story:\n";
    cout << "Remember: Enter [Exit] to cancel deleting a story.\n";

    while (true){
        bool Empty = Is_PLL_Empty(Personal_head);
        if (Empty){
            return;
        }
        else{
            cout << "What is the story ID you want to delete: ";
            getline(cin, Story_Id);
            // for cancellation
            if (Lower(Story_Id) == Keyword_to_cancel){
                break;
            }
            string id_maker = "Story " + Story_Id;

            bool Id_Exist = Is_StoryID_Exist(Personal_head, id_maker);

            if (Id_Exist){
                Personal_Node*  Title = Find_ID_Title(Personal_head, id_maker);
                while (true){
                    cout << "Do you want to delete [" << id_maker << "] title, [" << Title->data.Title << "][Y/N]: ";
                    getline(cin, Delete_Selection);
                    
                    if (Lower(Delete_Selection) == "y"){
                        Delete_Story_LinkL(Personal_head, id_maker);
                        ReIndex_Story_ID(Personal_head);
                        cout << Title->data.Title << " Have been deleted\n";
                        break;
                    }
                    else if(Lower(Delete_Selection) == "n"){
                        break;
                    }
                    else{
                        cout << "Invalid input\n";
                    }
                }
            }
        }
    }
}
// ------------------------weeeeh

// For Sharing a Story line of Code and Functions:
bool Check_Exist_InPub(Personal_Node* Personal_head,Public_Node* Public_head, string id_maker){
    Personal_Node* Personal_temp = Personal_head;
    Public_Node* Public_temp = Public_head;

    // Use a sub function in adding story
    Personal_Node* Title = Find_ID_Title(Personal_head, id_maker);

    string Lower_C_Title = Lower(Title->data.Title);
    while(Public_temp != nullptr){
        if(Lower_C_Title == Lower(Public_temp->data.Title)){
            return true; 
        }
        Public_temp = Public_temp->next;
    }

    return false;
}

string CreateID_Public(Public_Node* Public_head){
    int Count_Story = 0;
    Public_Node* temp = Public_head;

    while (temp != nullptr){
        Count_Story ++;
        temp = temp->next;
    }

    string id_maker = "Story " + to_string(Count_Story + 1);

        
    return id_maker;
}

void add_new_story_Pub(Public_Node*& Public_head, Personal_Node* Story) {
    if (Story == nullptr) {
        cout << "this problem";
        return;
    }

    Public_Section Public_story;
    Public_Node* newNode = new Public_Node();

    Public_story.ID = CreateID_Public(Public_head);
    Public_story.Title = Story->data.Title;
    Public_story.Type_of_MMM = Story->data.Type_of_MMM;
    Public_story.Story_status = Story->data.Story_status;
    Public_story.Genre_Counter = Story->data.Genre_Counter;
    Public_story.rev_rec.push_back(Story->data.rev_rec);

    newNode->data = Public_story;
    newNode->next = nullptr;

    if (Public_head == nullptr) {
        Public_head = newNode;
        return;
    }

    Public_Node* temp = Public_head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void update_existing_story_Pub(Public_Node*& Public_head, Personal_Node* Story){
    Public_Node* temp = Public_head;

    while(temp != nullptr){
        if(temp->data.Title == Story->data.Title){
            temp->data.rev_rec.push_back(Story->data.rev_rec);
            break;
        }
        temp = temp->next;
    }
}

void Share_Personal_list(Personal_Node* Personal_head, Public_Node*& Public_head){
    string Story_Id, Story_Id_Maker, Share_Selection;
    cin.ignore();
    cout << string(100, '-') << endl;
    cout << "Which Story do you want to share:\n";
    while (true){
        bool Empty = Is_PLL_Empty(Personal_head);
        if (Empty){
            return;
        }
        else{
            cout << "What is the story ID you want to share: ";
            getline(cin, Story_Id);
            // for cancellation
            if (Lower(Story_Id) == Keyword_to_cancel){
                break;
            }
            string id_maker = "Story " + Story_Id;

            bool Id_Exist = Is_StoryID_Exist(Personal_head, id_maker);

            if (!Id_Exist){
                cout << "Story ID not found.\n";
                continue;
            }
    
            Personal_Node* Story = Find_ID_Title(Personal_head, id_maker);
            if (Story == nullptr){
                cout << "Error retrieving story.\n";
                continue;
            }
            while (true){
                cout << "Do you want to share [" << id_maker << "] title, [" << Story->data.Title << "][Y/N]: ";
                getline(cin, Share_Selection);
                
                if (Lower(Share_Selection) == "y"){
                    bool Title_exist = Check_Exist_InPub(Personal_head, Public_head, id_maker);
                    
                    if (Title_exist){
                        update_existing_story_Pub(Public_head, Story);
                        cout <<"Story review and recommendation was Added in an existing story\n";
                        break;
                    }
                    else if (Title_exist == false){
                        add_new_story_Pub(Public_head, Story);
                        cout <<"New Story was Added\n";
                        break;
                    }
                }
                else if(Lower(Share_Selection) == "n"){
                    break;
                }
                else{
                    cout << "Invalid input\n";
                }
                
            }
        }   
    }
}

// ---------------------------weeeeh
// ==================================================== --------------------->


// =======This is the functions in the Personal list po --------------------->
// for Displaing Linked Lists Stories for Public:
void Display_Pub_L(Public_Node* Public_head) {
    Public_Node* Temp_Display = Public_head;

    cout << endl << string(100, '-') << endl;
    cout << "Welcome to Public List\n";

    if (Temp_Display == nullptr) {
        cout << "Public List is empty!\n";
        return;
    }

    while (Temp_Display != nullptr) {

        cout << Temp_Display->data.ID << ":\n";
        cout << "\tTitle: " << Temp_Display->data.Title << endl;
        cout << "\tType of Graphic Novel: " << Temp_Display->data.Type_of_MMM << endl;
        cout << "\tStory Status: " << Temp_Display->data.Story_status << endl;
        Temp_Display = Temp_Display->next;
    }
    cout << endl;
    cout << string(100, '-') << endl;
}

// For Public viewing line of Code and Functions:

void Search_via_title(Public_Node* Public_head){
    while (true){
        string Search_Title;
        cout << endl << string(100, '-') << endl;
        cout << "Title Search: ";
        getline(cin, Search_Title);

        // for cancellation
        if (Lower(Search_Title) == Keyword_to_cancel){
            break;
        }

        string Upper_C_Title = Upper(Search_Title);
        bool Story_exist = false;

        Public_Node* Temp_Public_Library = Public_head;
        
        while (Temp_Public_Library != nullptr){
            if (Upper_C_Title == Upper(Temp_Public_Library->data.Title)){
                Story_exist = true;
                cout << endl << string(100, '-') << endl;

                cout << Temp_Public_Library->data.ID << ":\n";
                cout << "\tTitle: " << Temp_Public_Library->data.Title << endl;
                cout << "\tType of Graphic Novel: " << Temp_Public_Library->data.Type_of_MMM << endl;
                cout << "\tStory Status: " << Temp_Public_Library->data.Story_status << endl;

                cout << "\tGenres: ";
                for (int i = 0; i < Temp_Public_Library->data.Genre_Counter; i++) {
                    cout << Temp_Public_Library->data.Genre[i];

                    if (i < Temp_Public_Library->data.Genre_Counter - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;

                cout << "\tReview and recommendations:\n";

                if (Temp_Public_Library->data.rev_rec.empty()) {
                    cout << "\t\t- No reviews yet\n";
                } 
                else {
                    for (int i = 0; i < Temp_Public_Library->data.rev_rec.size(); i++) {
                        cout << "\t\t- " << Temp_Public_Library->data.rev_rec[i] << endl;
                    }
                }
            }
        Temp_Public_Library = Temp_Public_Library->next;
        }
        if (!Story_exist){
            cout << "No story found with this title\n";
        }
    }
}

void View_By_Story_ID(Public_Node* Public_head){
    while (true){
        string Pick_Story_ID;
        cout << endl << string(100, '-') << endl;
        cout << "Which Story ID do you want to view: ";
        getline(cin, Pick_Story_ID);

        // for cancellation
        if (Lower(Pick_Story_ID) == Keyword_to_cancel){
            break;
        }

        string id_maker = "Story " + Pick_Story_ID;
        bool Story_exist = false;

        Public_Node* Temp_Public_Library = Public_head;
        
        while (Temp_Public_Library != nullptr){
            if (id_maker == Temp_Public_Library->data.ID){
                Story_exist = true;
                cout << endl << string(100, '-') << endl;

                cout << Temp_Public_Library->data.ID << ":\n";
                cout << "\tTitle: " << Temp_Public_Library->data.Title << endl;
                cout << "\tType of Graphic Novel: " << Temp_Public_Library->data.Type_of_MMM << endl;
                cout << "\tStory Status: " << Temp_Public_Library->data.Story_status << endl;

                cout << "\tGenres: ";
                for (int i = 0; i < Temp_Public_Library->data.Genre_Counter; i++) {
                    cout << Temp_Public_Library->data.Genre[i];

                    if (i < Temp_Public_Library->data.Genre_Counter - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;

                cout << "\tReview and recommendations:\n";

                if (Temp_Public_Library->data.rev_rec.empty()) {
                    cout << "\t\t- No reviews yet\n";
                } 
                else {
                    for (int i = 0; i < Temp_Public_Library->data.rev_rec.size(); i++) {
                        cout << "\t\t- " << Temp_Public_Library->data.rev_rec[i] << endl;
                    }
                }
            }
        Temp_Public_Library = Temp_Public_Library->next;
        }
        if (!Story_exist){
            cout << "No story found with this Story ID\n";
        }
    }
}

void View_by_Type_Novel(Public_Node* Public_head){
    string Type_Graphic_Novels[3] = {"Manwha", "Manhua" , "Manga"};
    string Pick_Novel;
    while (true){
        cout << endl << string(100, '-') << endl;
        cout << "Which Type of Graphic Novel do you want to view (Manwha/Manhua/Manga): ";
        getline(cin, Pick_Novel);

        // for cancellation
        if (Lower(Pick_Novel) == Keyword_to_cancel){
            break;
        }
        string Lower_C_MMM = Lower(Pick_Novel);
        bool Story_exist = false;

        bool Valid_Type = false;
        for (int i = 0; i < 3; i++) {
                if (Lower_C_MMM == Lower(Type_Graphic_Novels[i])){
                    Pick_Novel = Type_Graphic_Novels[i];
                    Valid_Type = true;
                }
        }
        if (!Valid_Type){
            cout << Pick_Novel << " is not in the graphic novel type.\n";
        }
        else if (Valid_Type){
            Public_Node* Temp_Public_Library = Public_head;
    
            while (Temp_Public_Library != nullptr){
                if (Pick_Novel == Temp_Public_Library->data.Type_of_MMM){
                    Story_exist = true;
                    cout << endl << string(100, '-') << endl;

                    cout << Temp_Public_Library->data.ID << ":\n";
                    cout << "\tTitle: " << Temp_Public_Library->data.Title << endl;
                    cout << "\tType of Graphic Novel: " << Temp_Public_Library->data.Type_of_MMM << endl;

                    cout << endl << string(100, '-') << endl;
                    cout << "From the Story Aboved:";
                    View_By_Story_ID(Public_head);
                    return;
                }
            Temp_Public_Library = Temp_Public_Library->next;
            }
            if (!Story_exist){
                cout << "No story found with this Graphic Novel type\n";
            }
        }
    }
}

void View_by_Story_Status(Public_Node* Public_head){
    string Pick_Status;
    string Story_Statuses[4] = {"Ongoing", "Completed", "Cancelled", "Hiatus"};

    while (true){
        cout << endl << string(100, '-') << endl;
        cout << "Which Type of Story status do you want to view (Ongoing/Completed/Cancelled/Hiatus): ";
        getline(cin, Pick_Status);
        string Lower_C_Status = Lower(Pick_Status);

        // for cancellation
        if (Lower_C_Status == Keyword_to_cancel){
            break;
        }
        bool Story_exist = false;   
        bool Valid_Status = false;

        for (int i = 0; i < 4; i++){
            if (Lower_C_Status == Lower(Story_Statuses[i])){
                Pick_Status = Story_Statuses[i];
                Valid_Status = true;
            }
        }

        if (!Valid_Status){
            cout << Pick_Status << " is not in the Story Status type.\n";
        }
        else{
            Public_Node* Temp_Public_Library = Public_head;

            while (Temp_Public_Library != nullptr){
                if (Pick_Status == Temp_Public_Library->data.Story_status){
                    Story_exist = true;

                    cout << Temp_Public_Library->data.ID << ":\n";
                    cout << "\tTitle: " << Temp_Public_Library->data.Title << endl;
                    cout << "\tStory Status: " << Temp_Public_Library->data.Story_status << endl;

                    cout << endl << string(100, '-') << endl;
                    cout << "From the Story Above:";
                    View_By_Story_ID(Public_head);
                    return;
                }

                Temp_Public_Library = Temp_Public_Library->next;
            }
            if (!Story_exist){
                cout << "No story found with this Story Status Type\n";
            }
        }
    }
}
    
// ---------------------------weeeeh

// for sample code only
void Add_Sample_Data(Personal_Node*& Personal_head){

    Personal_List s;
    s.ID = "Story 1"; 

    s.Title = "ONE PIECE";
    s.Type_of_MMM = "Manwha";
    s.Story_status = "Completed";

    s.Genre[0] = "Action";
    s.Genre[1] = "Fantasy";
    s.Genre[2] = "Adventure";

    s.Genre_Counter = 3; 
    s.rev_rec = "Very hype and good fights.";

    // insert to linked list (same as Add_Story)
    Personal_Node* newNode = new Personal_Node();
    newNode->data = s;
    newNode->next = nullptr;

    if (Personal_head == nullptr) {
        Personal_head = newNode;
    } else {
        Personal_Node* temp = Personal_head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }
}
void Add_Sample_Data_Public(Public_Node*& Public_head) {

    Public_Section s;

    s.ID = "Story 1";
    s.Title = "ONE PIECE";
    s.Type_of_MMM = "Manwha";
    s.Story_status = "Completed";

    // -----------------------
    // Genres (array style)
    // -----------------------
    s.Genre[0] = "Action";
    s.Genre[1] = "Fantasy";
    s.Genre[2] = "Adventure";

    s.Genre_Counter = 3;

    s.rev_rec.push_back("Love the Straw hats very much bruh.");

    
    Public_Node* newNode = new Public_Node();
    newNode->data = s;
    newNode->next = nullptr;

    if (Public_head == nullptr) {
        Public_head = newNode;
    } else {
        Public_Node* temp = Public_head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}