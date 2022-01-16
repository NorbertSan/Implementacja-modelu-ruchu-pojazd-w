import { useEffect, useRef, useState } from "react";

import { GET_GENERATED_CARS_AMOUNT_INTERVAL } from "../constants/timers";

const useGetGeneratedCarsStatistics = (boardObject) => {
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
};

export default useGetGeneratedCarsStatistics;
