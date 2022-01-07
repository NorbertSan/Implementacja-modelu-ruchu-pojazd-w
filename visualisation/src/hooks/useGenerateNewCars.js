import { useEffect, useRef, useState } from "react";
import {
  GENERATE_CARS_TIME_INTERVAL,
  GET_GENERATED_CARS_AMOUNT_INTERVAL,
} from "../constants/timers";

const useGenerateNewCars = (boardObject) => {
  const [generatedCarsAmount, setGeneratedCarsAmount] = useState(0);
  const [generatedCarsPerRoute, setGeneratedCarsPerRoute] = useState(null);
  const intervalRef = useRef(null);

  const setGetGeneratedCarsAmountInterval = () => {
    const interval = setInterval(() => {
      setGeneratedCarsAmount(boardObject.get_generated_cars_amount());
      setGeneratedCarsPerRoute(boardObject.get_generated_cars_per_route());
    }, GET_GENERATED_CARS_AMOUNT_INTERVAL);

    intervalRef.current = interval;
  };

  const clearGetGeneratedCarsAmountInterval = () => {
    if (intervalRef.current) {
      clearInterval(intervalRef.current);
      intervalRef.current = null;
    }
  };

  useEffect(() => {
    if (!boardObject) return;
    setGetGeneratedCarsAmountInterval();

    return () => clearGetGeneratedCarsAmountInterval;
  }, [boardObject]);

  return { generatedCarsAmount, generatedCarsPerRoute };

  // const intervalRef = useRef(null);

  // const setGenerateCarsInterval = () => {
  //   const interval = setInterval(() => {
  //     // FIXME: gdy generowane jest nowe auto nie jest one wyswietlane
  //     // nastepuje wywolanie metody update_positions i dopiero pobranie get_occupied_board
  //     // sprawa to wrazenie jakby auto nie było wygenerowane na pierwszej komórce ulicy

  //     boardObject.generate_new_cars();
  //   }, GENERATE_CARS_TIME_INTERVAL);
  //   intervalRef.current = interval;
  // };

  // const clearGenerateCarsInterval = () => {
  //   clearInterval(intervalRef.current);
  //   intervalRef.current = null;
  // };

  // useEffect(() => {
  //   if (!boardObject) return;
  //   setGenerateCarsInterval();

  //   return () => clearGenerateCarsInterval();
  // }, [boardObject]);
};

export default useGenerateNewCars;
