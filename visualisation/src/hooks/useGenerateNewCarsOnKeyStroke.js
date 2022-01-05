import { useEffect, useState } from "react";

const directionNumberDict = {
  DOWN: 1,
  UP: 2,
  RIGHT: 3,
  LEFT: 4,
};

const useGenerateNewCarsOnKeyStroke = (boardObject) => {
  const [areListenerSet, setAreListenerSet] = useState(false);

  useEffect(() => {
    if (!boardObject || areListenerSet) return;

    setAreListenerSet(true);

    document.addEventListener("keypress", (event) => {
      let initialCarDirection;
      let desiredCarDirection;

      switch (Number(event.key)) {
        case 1: {
          initialCarDirection = directionNumberDict.DOWN;
          desiredCarDirection = directionNumberDict.LEFT;
          break;
        }
        case 2: {
          initialCarDirection = directionNumberDict.DOWN;
          desiredCarDirection = directionNumberDict.DOWN;
          break;
        }
        case 3: {
          initialCarDirection = directionNumberDict.LEFT;
          desiredCarDirection = directionNumberDict.UP;
          break;
        }
        case 4: {
          initialCarDirection = directionNumberDict.LEFT;
          desiredCarDirection = directionNumberDict.LEFT;
          break;
        }
        case 5: {
          initialCarDirection = directionNumberDict.UP;
          desiredCarDirection = directionNumberDict.RIGHT;
          break;
        }
        case 6: {
          initialCarDirection = directionNumberDict.UP;
          desiredCarDirection = directionNumberDict.UP;
          break;
        }
        case 7: {
          initialCarDirection = directionNumberDict.RIGHT;
          desiredCarDirection = directionNumberDict.DOWN;
          break;
        }
        case 8: {
          initialCarDirection = directionNumberDict.RIGHT;
          desiredCarDirection = directionNumberDict.RIGHT;
          break;
        }
      }

      if (initialCarDirection && desiredCarDirection) {
        boardObject.generate_new_cars(initialCarDirection, desiredCarDirection);
      }
    });

    return () => {
      setAreListenerSet(false);
      document.removeEventListener("keypress", {});
    };
  }, [boardObject]);

  return;
};

export default useGenerateNewCarsOnKeyStroke;
