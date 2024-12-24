#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 100
#define MAX_LINE_LENGTH 256


void get_input(char *input_buffer, int size) {
    fgets(input_buffer, size, stdin);
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
}


int check_credentials(const char *username, const char *password) {
    FILE *file = fopen("database.csv", "r");
    if (file == NULL) {
        return 0; 
    }

    char line[MAX_LINE_LENGTH];
    char csv_username[MAX_INPUT_SIZE], csv_password[MAX_INPUT_SIZE];

    
    fgets(line, sizeof(line), file);

    
    while (fgets(line, sizeof(line), file)) {
       
        if (sscanf(line, "%99[^,],%99s", csv_username, csv_password) == 2) {
            
            if (strcmp(username, csv_username) == 0 && strcmp(password, csv_password) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0;  
}

int main() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    printf("Content-Type: text/html\n\n");

    
    get_input(username, MAX_INPUT_SIZE);  
    get_input(password, MAX_INPUT_SIZE);  

    
    printf("<html><head><title>Login Result</title></head><body>");
    printf("<h1>Cyber Cafe Management System</h1>");

   
    if (check_credentials(username, password)) {
        printf("<h3>Login Successful</h3>");
        printf("<p>Welcome, %s!</p>", username);
    } else {
        printf("<h3>Login Failed</h3>");
        printf("<p>Invalid username or password. Please try again.</p>");
    }

    printf("<a href='/index.html'>Go back to login</a>");
    printf("</body></html>");

    return 0;
}
