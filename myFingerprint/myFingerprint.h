#include <Adafruit_Fingerprint.h>

String Fingerprint_empty(int rx, int tx) {
  SoftwareSerial mySerial(2, 3);
  Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    return "Did not find fingerprint sensor.";
  }
  finger.emptyDatabase();
  return "OK";
}

String Fingerprint_scan(int rx, int tx) {
  SoftwareSerial mySerial(2, 3);
  Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    return "Did not find fingerprint sensor.";
  }
  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    return "Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.";
  }
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_NOFINGER:
      return "Enter your finger.";
    case FINGERPRINT_PACKETRECIEVEERR:
      return "Communication error";
    case FINGERPRINT_IMAGEFAIL:
      return "Imaging error";
    default:
      return "Unknown error";
  }
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return "Image too messy";
    case FINGERPRINT_PACKETRECIEVEERR:
      return "Communication error";
    case FINGERPRINT_FEATUREFAIL:
      return "Could not find fingerprint features";
    case FINGERPRINT_INVALIDIMAGE:
      return "Could not find fingerprint features";
    default:
      return "Unknown error";
  }
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {}
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    return"Communication error";
  } else if (p == FINGERPRINT_NOTFOUND) {
    return "Did not find a match";
  } else {
    return "Unknown error";
  }
  return String(finger.fingerID);
}

String Fingerprint_delete(int rx, int tx, int id) {
  int p = -1;
  SoftwareSerial mySerial(2, 3);
  Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    return "Did not find fingerprint sensor.";
  }
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK) {
    return "OK";
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    return "Communication error";
  } else if (p == FINGERPRINT_BADLOCATION) {
    return "Could not delete in that location";
  } else if (p == FINGERPRINT_FLASHERR) {
    return "Error writing to flash";
  } else {
    return "Unknown error";
  }
}


String Fingerprint_enroll(int rx, int tx, int id)
{
  int p = -1;
  SoftwareSerial mySerial(2, 3);
  Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    return "Did not find fingerprint sensor.";
  }
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        break;
      case FINGERPRINT_NOFINGER:
        return "Enter your finger.";
      case FINGERPRINT_PACKETRECIEVEERR:
        return "Communication error";
      case FINGERPRINT_IMAGEFAIL:
        return "Imaging error";
      default:
        return "Unknown error";
    }
  }

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return "Image too messy";
    case FINGERPRINT_PACKETRECIEVEERR:
      return "Communication error";
    case FINGERPRINT_FEATUREFAIL:
      return "Could not find fingerprint features";
    case FINGERPRINT_INVALIDIMAGE:
      return "Could not find fingerprint features";
    default:
      return "Unknown error";
  }
  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        break;
      case FINGERPRINT_NOFINGER:
        return "Enter your finger.";
      case FINGERPRINT_PACKETRECIEVEERR:
        return "Communication error";
      case FINGERPRINT_IMAGEFAIL:
        return "Imaging error";
      default:
        return "Unknown error";
    }
  }
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return "Image too messy";
    case FINGERPRINT_PACKETRECIEVEERR:
        return "Communication error";
      case FINGERPRINT_FEATUREFAIL:
          return "Could not find fingerprint features";
        case FINGERPRINT_INVALIDIMAGE:
            return "Could not find fingerprint features";
          default:
              return "Unknown error";
            }
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {}
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    return "Communication error";
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    return "Fingerprints did not match";
  } else {
    return "Unknown error";
  }
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    return "OK";
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    return "Communication error";
  } else if (p == FINGERPRINT_BADLOCATION) {
    return "Could not store in that location";
  } else if (p == FINGERPRINT_FLASHERR) {
    return"Error writing to flash";
  } else {
    return"Unknown error";
  }
}
