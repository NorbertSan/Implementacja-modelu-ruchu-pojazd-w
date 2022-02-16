import { useCallback, useEffect, useState } from "react";

import { CARS_AMOUNT_PER_ROAD_LANE_ARR } from "../constants/carsAmountToSimulation";
import { GENERATE_CARS_TIME_INTERVAL } from "../constants/timers";

const directionNumberDict = {
  DOWN: 1,
  UP: 2,
  RIGHT: 3,
  LEFT: 4,
};

const getCarDirection = (roadLane) => {
  let initialCarDirection;
  let desiredCarDirection;

  switch (Number(roadLane)) {
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

  return { initialCarDirection, desiredCarDirection };
};

const useGenerateNewCars = (
  boardObject,
  simulationStatus,
  generatedCarsPerRoute,
  setHasSimulationFinished,
  hasSimulationFinished,
  currentCarsAmount
) => {
  const [areListenerSet, setAreListenerSet] = useState(false);
  const [generateCarsOnLaneIntervals, setGenerateCarsOnLaneIntervals] =
    useState([]);

  const listenerFunction = useCallback(
    (event) => {
      const { initialCarDirection, desiredCarDirection } = getCarDirection(
        event.key
      );

      if (initialCarDirection && desiredCarDirection) {
        boardObject.generate_new_cars(initialCarDirection, desiredCarDirection);
      }
    },
    [boardObject]
  );

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

      generateCarsOnLaneIntervals.forEach((generateCarsOnLaneInterval) => {
        if (generateCarsOnLaneInterval)
          clearInterval(generateCarsOnLaneInterval);
      });
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

  useEffect(() => {
    if (!boardObject) return;

    const generateCarsIntervalsArr = [];

    for (let i = 0; i < 8; i++) {
      if (!CARS_AMOUNT_PER_ROAD_LANE_ARR[i])
        generateCarsIntervalsArr.push(null);
      else {
        setTimeout(() => {
          generateCarsIntervalsArr.push(
            setInterval(() => {
              const { initialCarDirection, desiredCarDirection } =
                getCarDirection(i + 1);

              boardObject.generate_new_cars(
                initialCarDirection,
                desiredCarDirection
              );
            }, GENERATE_CARS_TIME_INTERVAL)
          );
        }, i * 600);
      }
    }

    setGenerateCarsOnLaneIntervals(generateCarsIntervalsArr);
  }, [boardObject]);

  useEffect(() => {
    if (!generatedCarsPerRoute) return;

    for (let i = 0; i < 8; i++) {
      if (
        generateCarsOnLaneIntervals[i] &&
        generatedCarsPerRoute.get(i) >= CARS_AMOUNT_PER_ROAD_LANE_ARR[i]
      ) {
        const newGenerateCarsOnLaneIntervals = [...generateCarsOnLaneIntervals];
        newGenerateCarsOnLaneIntervals[i] = null;
        setGenerateCarsOnLaneIntervals(newGenerateCarsOnLaneIntervals);
        clearInterval(generateCarsOnLaneIntervals[i]);
      }
    }

    if (
      generateCarsOnLaneIntervals.every((interval) => !Boolean(interval)) &&
      currentCarsAmount === 0 &&
      !hasSimulationFinished
    ) {
      setHasSimulationFinished(true);
    }
  }, [generatedCarsPerRoute]);
  return;
};

export default useGenerateNewCars;
