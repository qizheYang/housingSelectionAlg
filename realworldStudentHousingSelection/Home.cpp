//
// Created by Charles Yang on 2025/2/12.
//

#include "Home.h"

int Home::calculateFactors() const {
    // price factor
    int augmentedPrice;
    if (price < 1800) {
        augmentedPrice = 1800;
    }
    else {
        augmentedPrice = price;
    }

    int augmentedAdditionalFactors = additionalFactors;

    if (augmentedPrice > 1800) {
        augmentedAdditionalFactors = additionalFactors - (augmentedPrice - 1800) / 100;
    }
    if (augmentedPrice > 2300) { // penalty for any price higher than 2300, considered much higher
        augmentedAdditionalFactors -= (augmentedPrice - 2300) / 10;
    }

    if (!includesUtilities()) {
        augmentedPrice += 150;
    }

    return
        // **Highest Priority (≈20 points each)**
            (bath ? 20 : -20) +  // Must-have, large penalty if missing
            ((sizeOfBedroom >= 300) ? ((sizeOfBedroom - 300) / 15) * 2 : -20) +  // Scaled bedroom size
            (privateWasherDryer ? 20 : -10) +  // Essential for convenience
            (dps ? 20 : 0) + // in DPS or not

            // **Mid-Priority (≈10-15 points each)**
            ((walkingTimeInMinutesToTaperHall <= 10) ? (10 - walkingTimeInMinutesToTaperHall) * 1.5 : -15) +  // Shorter walk = better
            (houseType * 7) +  // House type importance is similar to walking time
            ((augmentedPrice - 2450) / 50) +  // Price factor scaled

            // **Lower Priority (≈5-10 points each)**
            (ownerRating * 5) +  // Owner rating is relevant but secondary
            (waterElectricityInternet ? 7 : -5) +  // Utilities included = small benefit

            // **Lowest Priority (≈2-5 points each)**
            (haveGate ? 3 : 0) +  // Minimal impact features
            (haveSecurity ? 3 : 0) +
            (checkinTimeFlex ? 3 : 0) +

            // **Customizable Additional Factors**
            augmentedAdditionalFactors;
}
