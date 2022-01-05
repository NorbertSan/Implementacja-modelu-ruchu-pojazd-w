import { useEffect, useState } from "react";
import createModule from "../engine.mjs";

const useInitBoardModule = () => {
  const [WasmModule, setWasmModule] = useState(null);
  const [boardObject, setBoardObject] = useState(null);
  const [roadVector, setRoadVector] = useState([]);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    createModule()
      .then((WasmModule) => {
        setWasmModule(WasmModule);
        const board = new WasmModule.Board();
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
