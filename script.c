#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Print the content type header
    printf("Content-type: text/html\n\n");

    // Check if it's a POST request
    char* requestMethod = getenv("REQUEST_METHOD");
    if (requestMethod == NULL || strcmp(requestMethod, "POST") != 0) {
        printf("<html><body><p>Invalid request method</p></body></html>");
        return 1;
    }

    // Read the content length
    char* contentLengthStr = getenv("CONTENT_LENGTH");
    if (contentLengthStr == NULL) {
        printf("<html><body><p>Content length not specified</p></body></html>");
        return 1;
    }

    // Convert content length to integer
    int contentLength = atoi(contentLengthStr);

    // Allocate memory for the POST data
    char* postData = (char*)malloc(contentLength + 1);
    if (postData == NULL) {
        printf("<html><body><p>Memory allocation error</p></body></html>");
        return 1;
    }

    // Read the POST data
    if (fread(postData, 1, contentLength, stdin) != contentLength) {
        printf("<html><body><p>Error reading POST data</p></body></html>");
        free(postData);
        return 1;
    }

    // Null-terminate the POST data
    postData[contentLength] = '\0';

    // Parse username and password from POST data
    char* username = strtok(postData, "&=");
    char* password = strtok(NULL, "&=");

    // Check if the provided credentials are valid
    if (username != NULL && password != NULL &&
        strcmp(username, "bob") == 0 &&
        strcmp(password, "pass123") == 0) {
        // Redirect to dashboard.html
        printf("Location: dashboard.html\n\n");
    } else {
        // Print an error message if credentials are invalid
        printf("<html><body><p>Invalid username or password</p></body></html>");
    }

    // Free allocated memory
    free(postData);

    return 0;
}

