import { useEffect, useRef } from "react";
import { GENERATE_CARS_TIME_INTERVAL } from "../constants/timers";

const useGenerateNewCars = (boardObject) => {
  const intervalRef = useRef(null);

  const setGenerateCarsInterval = () => {
    const interval = setInterval(() => {
      // FIXME: gdy generowane jest nowe auto nie jest one wyswietlane
      // nastepuje wywolanie metody update_positions i dopiero pobranie get_occupied_board
      // sprawa to wrazenie jakby auto nie było wygenerowane na pierwszej komórce ulicy

      boardObject.generate_new_cars();
    }, GENERATE_CARS_TIME_INTERVAL);
    intervalRef.current = interval;
  };

  const clearGenerateCarsInterval = () => {
    clearInterval(intervalRef.current);
    intervalRef.current = null;
  };

  useEffect(() => {
    if (!boardObject) return;
    setGenerateCarsInterval();

    return () => clearGenerateCarsInterval();
  }, [boardObject]);
};

export default useGenerateNewCars;
