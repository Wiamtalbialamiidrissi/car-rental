#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100
#define CAR_DB_FILE "cars.csv"
#define MAX_CARS 100

typedef struct {
    int id;
    char brand[MAX_STRING_LENGTH];
    char model[MAX_STRING_LENGTH];
    char username[MAX_STRING_LENGTH];
    char fuelType[MAX_STRING_LENGTH];
    int numSeats;
    char transmission[MAX_STRING_LENGTH];
    float rentalPricePerDay;
    bool available;
} Car;

void addCar(FILE *file) {
    Car newCar;
    printf("Enter brand: ");
    scanf("%s", newCar.brand);
    printf("Enter model: ");
    scanf("%s", newCar.model);
    printf("Enter username: ");
    scanf("%s", newCar.username);
    printf("Enter fuel type: ");
    scanf("%s", newCar.fuelType);
    printf("Enter number of seats: ");
    scanf("%d", &newCar.numSeats);
    printf("Enter transmission type (automatic or manual): ");
    scanf("%s", newCar.transmission);
    printf("Enter rental price per day: ");
    scanf("%f", &newCar.rentalPricePerDay);
    newCar.available = true;

    fseek(file, 0, SEEK_END);
    fprintf(file, "%d,%s,%s,%s,%s,%d,%s,%.2f,%d\n", newCar.id, newCar.brand, newCar.model,
            newCar.username, newCar.fuelType, newCar.numSeats, newCar.transmission,
            newCar.rentalPricePerDay, newCar.available);
    printf("Car added successfully!\n");
}

void displayAllCars(FILE *file) {
    rewind(file);
    Car car;
    printf("\nAll Cars in the database:\n");
    printf("ID | Brand | Model | Username | Fuel Type | Seats | Transmission | Rental Price/Day | Available\n");
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &car.id, car.brand, car.model,
                  car.username, car.fuelType, &car.numSeats, car.transmission,
                  &car.rentalPricePerDay, &car.available) != EOF) {
        printf("%d | %s | %s | %s | %s | %d | %s | %.2f | %s\n", car.id, car.brand, car.model,
               car.username, car.fuelType, car.numSeats, car.transmission,
               car.rentalPricePerDay, car.available ? "Yes" : "No");
    }
}

void displayAvailableCars(FILE *file) {
    rewind(file);
    Car car;
    printf("\nAvailable Cars for Rental:\n");
    printf("ID | Brand | Model | Username | Fuel Type | Seats | Transmission | Rental Price/Day | Available\n");
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &car.id, car.brand, car.model,
                  car.username, car.fuelType, &car.numSeats, car.transmission,
                  &car.rentalPricePerDay, &car.available) != EOF) {
        if (car.available) {
            printf("%d | %s | %s | %s | %s | %d | %s | %.2f | %s\n", car.id, car.brand, car.model,
                   car.username, car.fuelType, car.numSeats, car.transmission,
                   car.rentalPricePerDay, car.available ? "Yes" : "No");
        }
    }
}

void searchCarsByBrandAndAvailability(FILE *file, const char *brand, bool availability) {
    rewind(file);
    Car car;
    printf("\nCars by Brand (%s) and Availability:\n", brand);
    printf("ID | Brand | Model | Username | Fuel Type | Seats | Transmission | Rental Price/Day | Available\n");
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &car.id, car.brand, car.model,
                  car.username, car.fuelType, &car.numSeats, car.transmission,
                  &car.rentalPricePerDay, &car.available) != EOF) {
        if (strcmp(car.brand, brand) == 0 && car.available == availability) {
            printf("%d | %s | %s | %s | %s | %d | %s | %.2f | %s\n", car.id, car.brand, car.model,
                   car.username, car.fuelType, car.numSeats, car.transmission,
                   car.rentalPricePerDay, car.available ? "Yes" : "No");
        }
    }
}

void bubbleSort(Car *cars, int n, bool (*compare)(Car, Car)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(cars[j], cars[j + 1])) {
                Car temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}

bool compareBrand(Car car1, Car car2) {
    return strcmp(car1.brand, car2.brand) > 0;
}

bool comparePricePerDay(Car car1, Car car2) {
    return car1.rentalPricePerDay > car2.rentalPricePerDay;
}

void sortByBrand(FILE *file) {
    rewind(file);
    Car cars[100];
    int count = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &cars[count].id, cars[count].brand, cars[count].model,
                  cars[count].username, cars[count].fuelType, &cars[count].numSeats, cars[count].transmission,
                  &cars[count].rentalPricePerDay, &cars[count].available) != EOF) {
        count++;
    }
    bubbleSort(cars, count, compareBrand);
    printf("\nCars Sorted by Brand:\n");
    printf("ID | Brand | Model | Username | Fuel Type | Seats | Transmission | Rental Price/Day | Available\n");
    for (int i = 0; i < count; i++) {
        printf("%d | %s | %s | %s | %s | %d | %s | %.2f | %s\n", cars[i].id, cars[i].brand, cars[i].model,
               cars[i].username, cars[i].fuelType, cars[i].numSeats, cars[i].transmission,
               cars[i].rentalPricePerDay, cars[i].available ? "Yes" : "No");
    }
}

void sortByPricePerDay(FILE *file) {
    rewind(file);
    Car cars[100];
    int count = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &cars[count].id, cars[count].brand, cars[count].model,
                  cars[count].username, cars[count].fuelType, &cars[count].numSeats, cars[count].transmission,
                  &cars[count].rentalPricePerDay, &cars[count].available) != EOF) {
        count++;
    }
}7
void loadDataFromFile(FILE *file, Car cars[], int *count) {
    rewind(file);
    *count = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%f,%d\n", &cars[*count].id, cars[*count].brand, cars[*count].model,
                  cars[*count].username, cars[*count].fuelType, &cars[*count].numSeats, cars[*count].transmission,
                  &cars[*count].rentalPricePerDay, &cars[*count].available) != EOF) {
        (*count)++;
    }
}

void saveDataToFile(FILE *file, Car cars[], int count) {
    fclose(file);
    file = fopen(CAR_DB_FILE, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%s,%.2f,%d\n", cars[i].id, cars[i].brand, cars[i].model,
            cars[i].username, cars[i].fuelType, cars[i].numSeats, cars[i].transmission,
            cars[i].rentalPricePerDay, cars[i].available);
    }
}

int findCarById(Car cars[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (cars[i].id == id) {
            return i;
        }
    }
    return -1; // Car not found
}

void modifyCar(Car cars[], int count) {
    int id;
    printf("Enter the ID of the car to modify: ");
    scanf("%d", &id);
    int index = findCarById(cars, count, id);
    if (index != -1) {
        printf("Enter new brand: ");
        scanf("%s", cars[index].brand);
        printf("Enter new model: ");
        scanf("%s", cars[index].model);
        printf("Enter new username: ");
        scanf("%s", cars[index].username);
        printf("Enter new fuel type: ");
        scanf("%s", cars[index].fuelType);
        printf("Enter new number of seats: ");
        scanf("%d", &cars[index].numSeats);
        printf("Enter new transmission type (automatic or manual): ");
        scanf("%s", cars[index].transmission);
        printf("Enter new rental price per day: ");
        scanf("%f", &cars[index].rentalPricePerDay);
        printf("Enter new availability (1 for available, 0 for not available): ");
        scanf("%d", &cars[index].available);
        printf("Car modified successfully!\n");
    } else {
        printf("Car with ID %d not found.\n", id);
    }
}

void deleteCar(Car cars[], int *count) {
    int id;
    printf("Enter the ID of the car to delete: ");
    scanf("%d", &id);
    int index = findCarById(cars, *count, id);
    if (index != -1) {
        for (int i = index; i < *count - 1; i++) {
            cars[i] = cars[i + 1];
        }
        (*count)--;
        printf("Car deleted successfully!\n");
    } else {
        printf("Car with ID %d not found.\n", id);
    }
}
int main() {
    FILE *carFile = fopen(CAR_DB_FILE, "a+");

    if (carFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Car cars[MAX_CARS];
    int carCount = 0;
    loadDataFromFile(carFile, cars, &carCount);

    int choice;
    do {
        printf("\nCar Rental Management System\n");
        printf("1. Add a Car\n");
        printf("2. Display All Cars\n");
        printf("3. Display Available Cars for Rental\n");
        printf("4. Search Cars by Brand and Availability\n");
        printf("5. Sort Cars by Brand\n");
        printf("6. Sort Cars by Price Per Day\n");
        printf("7. Modify a Car\n");
        printf("8. Delete a Car\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCar(carFile);
                loadDataFromFile(carFile, cars, &carCount);
                break;
            case 2:
                displayAllCars(carFile);
                break;
            case 3:
                displayAvailableCars(carFile);
                break;
            case 4: {
                printf("Enter brand to search: ");
                char brand[MAX_STRING_LENGTH];
                scanf("%s", brand);
                printf("Enter availability (1 for available, 0 for not available): ");
                bool availability;
                scanf("%d", &availability);
                searchCarsByBrandAndAvailability(carFile, brand, availability);
                break;
            }
            case 5:
                sortByBrand(carFile);
                break;
            case 6:
                sortByPricePerDay(carFile);
                break;
            case 7:
                modifyCar(cars, carCount);
                saveDataToFile(carFile, cars, carCount);
                break;
            case 8:
                deleteCar(cars, &carCount);
                saveDataToFile(carFile, cars, carCount);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 9);

    fclose(carFile);
    return 0;
}