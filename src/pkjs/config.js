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
        "defaultValue": "Background & Center"
      },
      {
        "type": "color",
        "messageKey": "ColorBackground",
        "label": "Background Color",
        "defaultValue": "000000",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorBackground",
        "label": "Background Color",
        "defaultValue": "000000",
        "sunlight": false,
        "layout": "BLACK_WHITE",
        "capabilities": ["BW"]
      },
      {
        "type": "color",
        "messageKey": "ColorCenterCircle",
        "label": "Center Dot",
        "defaultValue": "FFFFFF",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorCenterCircle",
        "label": "Center Dot",
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
        "defaultValue": "Hands"
      },
      {
        "type": "color",
        "messageKey": "ColorHourHand",
        "label": "Hour Hand",
        "defaultValue": "AAAAAA",
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
      },
      {
        "type": "slider",
        "messageKey": "HandTailLength",
        "label": "Hand Tail Extension (px)",
        "defaultValue": 8,
        "min": 0,
        "max": 20,
        "step": 1
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
        "defaultValue": "55AAFF",
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
        "defaultValue": "Data"
      },
      {
        "type": "select",
        "messageKey": "Data",
        "label": "Data Display",
        "defaultValue": "date",
        "capabilities": ["HEART_RATE"],
        "options": [
          { "label": "None", "value": "none" },
          { "label": "Heart Rate", "value": "heart_rate" },
          { "label": "Date", "value": "date" }
        ]
      },
      {
        "type": "select",
        "messageKey": "Data",
        "label": "Data Display",
        "defaultValue": "date",
        "capabilities": ["NOT_HEART_RATE"],
        "options": [
          { "label": "None", "value": "none" },
          { "label": "Date", "value": "date" }
        ]
      },
      {
        "type": "select",
        "messageKey": "DateFormat",
        "label": "Date Format",
        "defaultValue": "dd MMM",
        "options": [
          { "label": "dd MMM", "value": "dd MMM" },
          { "label": "MMM dd", "value": "MMM dd" }
        ]
      },
      {
        "type": "color",
        "messageKey": "ColorHeartRate",
        "label": "Data Color",
        "defaultValue": "FFFFFF",
        "sunlight": true,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "ColorHeartRate",
        "label": "Data Color",
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

