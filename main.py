import uvicorn
from fastapi import FastAPI, Query
from pydantic import Field
from pydantic.main import BaseModel

app = FastAPI(title="Smart LED")


class DataModel(BaseModel):
    mode: int = Field(ge=1, le=1, default=1)
    submode: int = Field(ge=1, le=3, default=1)


data = DataModel()


@app.get('/getData', response_model=DataModel)
def get_data():
    return data


@app.put('/setMode', response_model=DataModel)
def set_mode(new_mode: int = Query(ge=1, le=1, default=1)):
    global data
    data.mode = new_mode
    return data


@app.put('/setSubmode', response_model=DataModel)
def set_submode(new_submode: int = Query(ge=1, le=3, default=1)):
    global data
    data.submode = new_submode
    return data


uvicorn.run(app)