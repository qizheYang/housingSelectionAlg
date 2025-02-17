//
// Created by Charles Yang on 2025/2/12.
//

#ifndef REALWORLDSTUDENTHOUSINGSELECTION_HOME_H
#define REALWORLDSTUDENTHOUSINGSELECTION_HOME_H

#include <string>

class Home {
private:
    std::string name;
    int ownerRating;
    int houseType; // 0=公寓, 1=叠层, 2=别墅
    // houseType 实际上代表1B或者Studio
    std::string roomType;
    // roomType 实际上代表房子的类型
    std::string location;
    int walkingTimeInMinutesToTaperHall;
    int price;
    bool checkinTimeFlex;
    bool furnished;
    bool haveGate;
    bool haveSecurity;
    bool waterElectricityInternet;
    bool bath;
    int sizeOfBedroom; // sqft
    bool privateWasherDryer;
    int additionalFactors;
    bool dps;

public:
    // Constructor
    Home() : name(""), ownerRating(0), houseType(0), roomType(""),
             location(""), walkingTimeInMinutesToTaperHall(0), price(0),
             checkinTimeFlex(false), furnished(false), haveGate(false),
             haveSecurity(false), waterElectricityInternet(false), bath(false),
             sizeOfBedroom(0), privateWasherDryer(false), additionalFactors(0), dps(0) {}

    Home(std::string name, int ownerRating, int houseType, std::string roomType,
         std::string location, int walkingTimeInMinutesToTaperHall, int price, bool checkinTimeFlex,
         bool furnished, bool haveGate, bool haveSecurity, bool waterElectricityInternet, bool bath,
         int sizeOfBedroom, bool privateWasherDryer, int additionalFactors, bool dps)
            : name(name), ownerRating(ownerRating), houseType(houseType), roomType(roomType),
              location(location), walkingTimeInMinutesToTaperHall(walkingTimeInMinutesToTaperHall),
              price(price), checkinTimeFlex(checkinTimeFlex), furnished(furnished),
              haveGate(haveGate), haveSecurity(haveSecurity),
              waterElectricityInternet(waterElectricityInternet), bath(bath),
              sizeOfBedroom(sizeOfBedroom), privateWasherDryer(privateWasherDryer),
              additionalFactors(additionalFactors), dps(dps) {}

    // Getters and setters (optional, based on need)
    std::string getName() const { return name; }
    int getOwnerRating() const { return ownerRating; }
    int getHouseType() const { return houseType; }
    std::string getRoomType() const { return roomType; }
    std::string getLocation() const { return location; }
    int getWalkingTimeToTaperHall() const { return walkingTimeInMinutesToTaperHall; }
    int getPrice() const { return price; }
    bool isCheckinTimeFlexible() const { return checkinTimeFlex; }
    bool isFurnished() const { return furnished; }
    bool hasGate() const { return haveGate; }
    bool hasSecurity() const { return haveSecurity; }
    bool includesUtilities() const { return waterElectricityInternet; }
    bool hasBath() const { return bath; }
    int getSizeOfBedroom() const { return sizeOfBedroom; }
    bool hasPrivateWasherDryer() const { return privateWasherDryer; }
    int getAdditionalFactors() const { return additionalFactors; }
    bool inDps() const { return dps; }

    int calculateFactors() const;
};

#endif //REALWORLDSTUDENTHOUSINGSELECTION_HOME_H
