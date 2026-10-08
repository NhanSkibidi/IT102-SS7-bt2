#include <stdio.h>
#include <string.h>
struct SmartDevice {
int deviceID;
char deviceName[100];
int status;
float ratedPowerKW;
};
struct EnergySensor {
float voltageVolts;
float currentAmperes;
int unoccupancyMinutes;
};
int main() {
struct SmartDevice device;
struct EnergySensor sensor;
float operatingHours;
float energyKWh;
float electricityCost = 0.0f;
printf("=== RIKEI SMARTHOME ===\n");
printf("Nhap ma thiet bi: ");
scanf("%d", &device.deviceID);
while (getchar() != '\n');
printf("Nhap ten thiet bi: ");
fgets(device.deviceName, sizeof(device.deviceName), stdin);
device.deviceName[strcspn(device.deviceName, "\n")] = '\0';
printf("Nhap trang thai thiet bi (1-Bat, 0-Tat): ");
scanf("%d", &device.status);
printf("Nhap cong suat dinh muc (kW): ");
scanf("%f", &device.ratedPowerKW);
printf("Nhap dien ap do duoc (V): ");
scanf("%f", &sensor.voltageVolts);
printf("Nhap dong dien do duoc (A): ");
scanf("%f", &sensor.currentAmperes);
printf("Nhap thoi gian vang nguoi (phut): ");
scanf("%d", &sensor.unoccupancyMinutes);
printf("Nhap so gio hoat dong trong thang: ");
scanf("%f", &operatingHours);
if (sensor.voltageVolts < 0 ||
    sensor.currentAmperes < 0 ||
    sensor.unoccupancyMinutes < 0) {
    printf("\nLoi: Du lieu cam bien khong hop le.\n");
    printf("He thong huy thao tac xu ly.\n");
    return 0;
}
if (operatingHours <= 0 || operatingHours > 744) {
    printf("\nLoi: So gio van hanh phai lon hon 0 va khong vuot qua 744 gio.\n");
    printf("He thong tu choi tinh toan hoa don.\n");
    return 0;
}
if (device.status == 1) {
    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;
        printf("\nCANH BAO: Dong dien vuot qua 30.0A!\n");
        printf("Nguy co qua tai va chay no.\n");
        printf("He thong da ngat thiet bi khan cap.\n");
    } else if (sensor.unoccupancyMinutes >= 15) {
        device.status = 0;
        printf("\nCANH BAO: Phong vang nguoi tu 15 phut tro len.\n");
        printf("He thong da tu dong tat thiet bi de tiet kiem nang luong.\n");
    }
}
energyKWh = device.ratedPowerKW * operatingHours;
if (energyKWh <= 50) {
    electricityCost = energyKWh * 1806;
} else if (energyKWh <= 100) {
    electricityCost = 50 * 1806;
    electricityCost += (energyKWh - 50) * 1866;
} else if (energyKWh <= 200) {
    electricityCost = 50 * 1806;
    electricityCost += 50 * 1866;
    electricityCost += (energyKWh - 100) * 2167;
} else {
    electricityCost = 50 * 1806;
    electricityCost += 50 * 1866;
    electricityCost += 100 * 2167;
    electricityCost += (energyKWh - 200) * 2729;
}
printf("\n=== BAO CAO HE THONG ===\n");
printf("Ma thiet bi: %d\n", device.deviceID);
printf("Ten thiet bi: %s\n", device.deviceName);
printf("Trang thai: %s\n", device.status == 1 ? "DANG BAT" : "DA TAT");
printf("Cong suat dinh muc: %.2f kW\n", device.ratedPowerKW);
printf("Dien ap: %.2f V\n", sensor.voltageVolts);
printf("Dong dien: %.2f A\n", sensor.currentAmperes);
printf("Thoi gian vang nguoi: %d phut\n", sensor.unoccupancyMinutes);
printf("So gio hoat dong: %.2f gio\n", operatingHours);
printf("Tong dien nang: %.2f kWh\n", energyKWh);
printf("Tien dien: %.0f VND\n", electricityCost);
printf("Tien dien chua bao gom VAT.\n");
return 0;
}
