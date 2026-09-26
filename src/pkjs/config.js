module.exports = [
  {
    "type": "heading",
    "defaultValue": "Halo Swipe",
    "size": 1
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Hands"
      },
      {
        "type": "color",
        "messageKey": "ColorHourHand",
        "label": "Hour Hand",
        "defaultValue": "FFFFFF",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorHourHand",
        "label": "Hour Hand",
        "defaultValue": "FFFFFF",
        "sunlight": false,
        "layout": "BLACK_WHITE",
        "capabilities": ["BW"]
      },
      {
        "type": "color",
        "messageKey": "ColorMinuteHand",
        "label": "Minute Hand",
        "defaultValue": "FFFFFF",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorMinuteHand",
        "label": "Minute Hand",
        "defaultValue": "FFFFFF",
        "sunlight": false,
        "layout": "BLACK_WHITE",
        "capabilities": ["BW"]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Halos"
      },
      {
        "type": "color",
        "messageKey": "ColorMinuteHalo",
        "label": "Minute Halo",
        "defaultValue": "FFFFFF",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorMinuteHalo",
        "label": "Minute Halo",
        "defaultValue": "FFFFFF",
        "sunlight": false,
        "layout": "BLACK_WHITE",
        "capabilities": ["BW"]
      },
      {
        "type": "color",
        "messageKey": "ColorHaloBackground",
        "label": "Halo Background",
        "defaultValue": "555555",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorHaloBackground",
        "label": "Halo Background",
        "defaultValue": "AAAAAA",
        "sunlight": false,
        "allowGray": true,
        "layout": "GRAY",
        "capabilities": ["BW"]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Heart Rate"
      },
      {
        "type": "color",
        "messageKey": "ColorHeartRate",
        "label": "Heart Rate",
        "defaultValue": "FFFFFF",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorHeartRate",
        "label": "Heart Rate",
        "defaultValue": "FFFFFF",
        "sunlight": false,
        "layout": "BLACK_WHITE",
        "capabilities": ["BW"]
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save"
  }
];

