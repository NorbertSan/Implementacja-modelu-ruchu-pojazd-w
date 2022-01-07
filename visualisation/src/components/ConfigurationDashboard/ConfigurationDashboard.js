import { useEffect, useState } from "react";
import Button from "@mui/material/Button";
import AddIcon from "@mui/icons-material/Add";
import RemoveIcon from "@mui/icons-material/Remove";
import styles from "./ConfigurationDashboard.module.scss";
import TextField from "@mui/material/TextField";
import cx from "classnames";

const ConfigurationDashboard = ({
  WasmModule,
  toggleSimulationStatus,
  simulationStatus,
}) => {
  const [maxSpeed, setMaxSpeed] = useState(null);
  const [maxPossibleSpeed, setMaxPossibleSpeed] = useState(null);
  const [randomBrakingProbability, setRandomBrakingProbability] =
    useState(null);

  useEffect(() => {
    if (!WasmModule) return;
    setMaxSpeed(WasmModule.get_max_speed());
    setMaxPossibleSpeed(WasmModule.get_max_possible_speed());
    setRandomBrakingProbability(WasmModule.get_random_braking_probability());
  }, [WasmModule]);

  if (maxSpeed === null || randomBrakingProbability === null) return null;

  const incrementMaxSpeed = () => {
    const newSpeed = maxSpeed + 1;
    WasmModule.set_max_speed(newSpeed);
    setMaxSpeed(newSpeed);
  };

  const reduceMaxSpeed = () => {
    const newSpeed = maxSpeed - 1;
    WasmModule.set_max_speed(newSpeed);
    setMaxSpeed(newSpeed);
  };

  const handleBrakingProbabilityChange = (event) => {
    const newValue = Number(event.target.value);
    if (newValue < 0 || newValue > 100) return;
    WasmModule.set_random_braking_probability(newValue);
    setRandomBrakingProbability(newValue);
  };

  return (
    <div>
      <div className={styles.container}>
        <span>Maksymalna prędkość: </span>
        <div className={styles["flex-center"]}>
          <Button
            onClick={reduceMaxSpeed}
            disabled={maxSpeed < 2}
            size="small"
            variant="contained"
          >
            <RemoveIcon />
          </Button>
          <span className={cx(styles["font-md"], styles["m-x"])}>
            {maxSpeed}
          </span>
          <Button
            disabled={maxSpeed === maxPossibleSpeed}
            onClick={incrementMaxSpeed}
            size="small"
            variant="contained"
          >
            <AddIcon />
          </Button>
        </div>
      </div>
      <div className={styles.container}>
        <span>Prawdopodobieństwo losowego zahamowania (%): </span>
        <TextField
          value={randomBrakingProbability}
          size="small"
          id="outlined-number"
          label="Number"
          type="number"
          onChange={handleBrakingProbabilityChange}
        />
      </div>
      <div className={styles["simulation-state-container"]}>
        <Button
          onClick={toggleSimulationStatus}
          size="large"
          variant="contained"
        >
          {simulationStatus ? "STOP" : "START"}
        </Button>
      </div>
    </div>
  );
};

export default ConfigurationDashboard;
