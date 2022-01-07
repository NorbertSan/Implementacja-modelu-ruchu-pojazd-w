import styles from "./StatisticsDashboard.module.scss";
import Box from "@mui/material/Box";
import { useEffect, useState } from "react";

const StatisticsDashboard = ({
  updatesAmount,
  generatedCarsAmount,
  currentCarsAmount,
  generatedCarsPerRoute,
}) => {
  const [carsPerRouteDivs, setCarsPerRouteDivs] = useState([]);

  useEffect(() => {
    const carsPerRouteDivsTemp = [];

    for (let i = 0; i < 8; i++)
      carsPerRouteDivsTemp.push(
        <div key={i} className={styles.grid}>
          <span>Pas {i + 1}:</span>
          <span>
            {generatedCarsPerRoute ? generatedCarsPerRoute.get(i) : 0}
          </span>
        </div>
      );

    setCarsPerRouteDivs(carsPerRouteDivsTemp);
  }, [generatedCarsPerRoute]);

  return (
    <Box sx={{ boxShadow: 2 }}>
      <div className={styles.wrapper}>
        <h3 className={styles.title}>Statystyki</h3>

        <div className={styles.grid}>
          <span>Liczba okrążeń:</span>
          <span>{updatesAmount}</span>
        </div>

        <h4 className={styles.title}>Wygenerowane auta</h4>
        <div className={styles.grid}>
          <span>Łącznie:</span>
          <span>{generatedCarsAmount}</span>
        </div>

        <div
          style={{
            marginBottom: 30,
          }}
          className={styles.grid}
        >
          <span>Obecne:</span>
          <span>{currentCarsAmount}</span>
        </div>

        {carsPerRouteDivs}
      </div>
    </Box>
  );
};

export default StatisticsDashboard;
