import { useCallback, useEffect, useState } from "react";

const directionNumberDict = {
  DOWN: 1,
  UP: 2,
  RIGHT: 3,
  LEFT: 4,
};

const useGenerateNewCarsOnKeyStroke = (boardObject, simulationStatus) => {
  const [areListenerSet, setAreListenerSet] = useState(false);

  const listenerFunction = useCallback(() => {
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
  }, [boardObject]);

  const addListenerToDocument = () => {
    document.addEventListener("keypress", listenerFunction, true);
  };

  useEffect(() => {
    if (!boardObject || areListenerSet) return;

    setAreListenerSet(true);

    addListenerToDocument();

    return () => {
      setAreListenerSet(false);
      document.removeEventListener("keypress", listenerFunction, true);
    };
  }, [boardObject]);

  useEffect(() => {
    if (
      (simulationStatus && areListenerSet) ||
      (!simulationStatus && !areListenerSet) ||
      !boardObject
    )
      return;

    if (!simulationStatus) {
      setAreListenerSet(false);
      document.removeEventListener("keypress", listenerFunction, true);
    }

    if (simulationStatus) {
      setAreListenerSet(true);
      addListenerToDocument();
    }
  }, [simulationStatus]);

  return;
};

export default useGenerateNewCarsOnKeyStroke;
