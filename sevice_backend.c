#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 100


void get_input(char *input_buffer, int size) {
    fgets(input_buffer, size, stdin);
    input_buffer[strcspn(input_buffer, "\n")] = '\0';  
}


void save_session_data(const char *service, int time_left) {
    FILE *file = fopen("session_data.txt", "w");
    if (file == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h3>Error: Could not save session data.</h3></body></html>");
        exit(1);
    }

    fprintf(file, "Service: %s\n", service);
    fprintf(file, "Time Left: %d minutes\n", time_left);
    fclose(file);
}


void handle_service_selection(const char *service) {
    int time_left = 30;  

   
    save_session_data(service, time_left);

    
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Service Started</title></head><body>");
    printf("<h1>Cyber Cafe Service</h1>");
    printf("<h3>Service: %s</h3>", service);
    printf("<p>Session started. You have %d minutes for this service.</p>", time_left);
    printf("<p><a href='/cgi-bin/service.cgi?extend=true'>Extend Session</a></p>");
    printf("<p><a href='/cgi-bin/service.cgi?end=true'>End Session</a></p>");
    printf("</body></html>");
}

void extend_session() {
    
    FILE *file = fopen("session_data.txt", "r");
    if (file == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h3>Error: No session data found.</h3></body></html>");
        exit(1);
    }

   
    char service[MAX_INPUT_SIZE];
    int time_left;
    fscanf(file, "Service: %s\n", service);
    fscanf(file, "Time Left: %d\n", &time_left);
    fclose(file);

   
    time_left += 15; 

    
    save_session_data(service, time_left);

   
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Session Extended</title></head><body>");
    printf("<h1>Cyber Cafe Service</h1>");
    printf("<h3>Your %s session has been extended!</h3>", service);
    printf("<p>You now have %d more minutes.</p>", time_left);
    printf("<p><a href='/cgi-bin/service.cgi?end=true'>End Session</a></p>");
    printf("</body></html>");
}

void end_session() {
    
    remove("session_data.txt");

    
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Session Ended</title></head><body>");
    printf("<h1>Cyber Cafe Service</h1>");
    printf("<h3>Your session has ended.</h3>");
    printf("<p><a href='/'>Go back to service selection</a></p>");
    printf("</body></html>");
}

int main() {
   
    char query_string[MAX_INPUT_SIZE];
    char service[MAX_INPUT_SIZE];

    
    fgets(query_string, MAX_INPUT_SIZE, stdin);
    
    
    if (strstr(query_string, "service=") != NULL) {
        sscanf(query_string, "service=%s", service);
        handle_service_selection(service); 
    } else if (strstr(query_string, "extend=true") != NULL) {
        extend_session(); 
    } else if (strstr(query_string, "end=true") != NULL) {
        end_session();  
    } else {
        
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Choose Service</title></head><body>");
        printf("<h1>Cyber Cafe Service</h1>");
        printf("<h2>Select a Service:</h2>");
        printf("<p><a href='/cgi-bin/service.cgi?service=browse'>Browse</a></p>");
        printf("<p><a href='/cgi-bin/service.cgi?service=print'>Print</a></p>");
        printf("</body></html>");
    }

    return 0;
}
