import uvicorn
from fastapi import FastAPI, Query, HTTPException
from pydantic import Field
from pydantic.main import BaseModel

app = FastAPI(title="Smart LED")


class DataModel(BaseModel):
    mode: int = Field(ge=1, le=4, default=1)
    submode: int = Field(ge=1, le=9, default=1)
    settings_0: int = Field(ge=0, le=255, default=90)
    settings_1: int = Field(ge=0, le=255, default=255)


data = DataModel()
limits = {
    1: {
        1: [(15, 0, 180), (15, 0, 255)],
        2: [(), (10, 0, 255)],
        3: [(10, 0, 255), (10, 0, 255)]
    }
}


@app.get('/getData', response_model=DataModel)
def get_data():
    return data


@app.put('/setModeAndSubmode', response_model=DataModel)
def set_mode(new_mode: int = Query(ge=1, le=4, default=1), new_submode: int = Query(ge=1, le=9, default=1)):
    global data
    data.mode = new_mode
    data.submode = new_submode
    return data


# Set higher
@app.get('/setSet0Higher', response_model=DataModel)
def set_settings0_higher():
    global data
    data.settings_0 = max(
        limits[data.mode][data.submode][0][1],
        min(
            limits[data.mode][data.submode][0][2],
            data.settings_0 + limits[data.mode][data.submode][0][0]
        )
    )
    return data


@app.get('/setSet1Higher', response_model=DataModel)
def set_settings1_higher():
    global data
    data.settings_1 = max(
        limits[data.mode][data.submode][1][1],
        min(
            limits[data.mode][data.submode][1][2],
            data.settings_1 + limits[data.mode][data.submode][1][0]
        )
    )
    return data


# Set lower
@app.get('/setSet0Lower', response_model=DataModel)
def set_settings0_lower():
    global data
    data.settings_0 = max(
        limits[data.mode][data.submode][0][1],
        min(
            limits[data.mode][data.submode][0][2],
            data.settings_0 - limits[data.mode][data.submode][0][0]
        )
    )
    return data


@app.get('/setSet1Lower', response_model=DataModel)
def set_settings1_lower():
    global data
    data.settings_1 = max(
        limits[data.mode][data.submode][1][1],
        min(
            limits[data.mode][data.submode][1][2],
            data.settings_1 - limits[data.mode][data.submode][1][0]
        )
    )
    return data


# Set max
@app.get('/setSet0Max', response_model=DataModel)
def set_settings0_max():
    global data
    data.settings_0 = limits[data.mode][data.submode][0][2]
    return data


@app.get('/setSet1Max', response_model=DataModel)
def set_settings1_max():
    global data
    data.settings_1 = limits[data.mode][data.submode][1][2]
    return data


# Set min
@app.get('/setSet0Min', response_model=DataModel)
def set_settings0_min():
    global data
    data.settings_0 = limits[data.mode][data.submode][0][1]
    return data


@app.get('/setSet1Min', response_model=DataModel)
def set_settings1_min():
    global data
    data.settings_1 = limits[data.mode][data.submode][1][1]
    return data
