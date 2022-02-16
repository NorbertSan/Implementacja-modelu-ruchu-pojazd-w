import { useEffect, useState } from "react";
import createModule from "../engine.mjs";

const MAIN_ROAD_DICT = {
  NONE: 5,
  UP_DOWN: 6,
};

const useInitBoardModule = () => {
  const [WasmModule, setWasmModule] = useState(null);
  const [boardObject, setBoardObject] = useState(null);
  const [roadVector, setRoadVector] = useState([]);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const mainRoad =
      process.env.REACT_APP_CROSSROAD_VERSION == 1
        ? MAIN_ROAD_DICT.UP_DOWN
        : MAIN_ROAD_DICT.NONE;

    createModule()
      .then((WasmModule) => {
        setWasmModule(WasmModule);
        const board = new WasmModule.Board(mainRoad);
        setBoardObject(board);
        setRoadVector(board.get_road_board());
        setLoading(false);
      })
      .catch((error) => {
        setError(error);
        setLoading(false);
        throw error;
      });
  }, []);
  return {
    WasmModule,
    error,
    loading,
    boardObject,
    roadVector,
  };
};

export default useInitBoardModule;
