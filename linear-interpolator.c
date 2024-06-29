#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX_INPUT_SIZE = 100;

void clear_input_buffer() {
    while (getchar() != '\n');
}

double linear_interpolate(
    double lead1, double lead2, double lead3,
    double tail1, double tail3
) {
	return tail1 + (tail3 - tail1) * (lead2 - lead1) / (lead3 - lead1);
}

int get_batches_number() {
    int batches_input;

    while (1) {
        printf("Number of batches (1-5): ");
        batches_input = getchar();
        clear_input_buffer();

        if (isdigit(batches_input) && batches_input != ' ') {
            break;
        } else {
            printf("Invalid input. Try again.\n");
        }
    }
    return batches_input - '0';
}

double input_double() {
    char lead_input[MAX_INPUT_SIZE];
    double lead;
    char *conversion_endptr;

    if(fgets(lead_input, sizeof(lead_input), stdin)) {
        size_t input_len = strlen(lead_input);
        if(input_len > 0 && lead_input[input_len - 1] == '\n') {
            lead_input[input_len - 1] = '\0';
        }

        lead = strtod(lead_input, &conversion_endptr);
        if (*conversion_endptr != '\0') {
            printf("Input is too long. The limit is 100 digits.\n");
            return -1;
        } else {
            return lead;
        }
    } else {
        printf("input_number :: error getting lead input\n");
        return -1;
    }
}

void get_leads(double leads[3]) {
    printf("############# Leads #############\n");
    for(int i = 0; i < 3; i++) {
        double lead;
        printf("Enter lead %d: ", i + 1);
        lead = input_double();
        if (lead != -1) {
            leads[i] = lead;
        }
    }
}

void get_tails(double tails[], int batches_number) {
    int batch_indx = 0;
    while (batch_indx < batches_number) {
        printf("############# Batch %d #############\n", batch_indx + 1);
        for (int i = 0; i < 2; i++) {
            double tail;
            printf("Enter lead %d: ", i + 1);
            tail = input_double();
            if (tail != -1) {
                tails[batch_indx * 2 + i] = tail;
            } 
        }
        batch_indx++;
    }
}

void calculate_tails(int batches, double leads[], double tails[], double results[]) {
    for (int i = 0; i < batches; i++) {
        double result = linear_interpolate(
            leads[0], leads[1], leads[2], tails[i * 2], tails[i * 2 + 1]
        );
        results[i] = result;
    }
}

void show_results(int batches, double results[]) {
    printf("############# Results #############\n");
    for (int i = 0; i < batches; i++) {
        printf("Result for batch %d: %0.4f", i, results[i]);
    }
}

int main() {
    printf("A simple linear interpolator\n");
    int batches = get_batches_number();
    double leads[3];
    double tails[batches * 2];
    double results[batches];
    get_leads(leads);
    get_tails(tails, batches);
    calculate_tails(batches, leads, tails, results);
    show_results(batches, results);
}
