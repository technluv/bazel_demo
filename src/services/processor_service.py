from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List
import ctypes
import numpy as np
import os

app = FastAPI()

# Load C++ library
lib_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../libprocessor.so'))
lib = ctypes.CDLL(lib_path)

# Define C++ function interfaces
lib.process_data.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS'),
    ctypes.c_int,
    np.ctypeslib.ndpointer(dtype=np.float64, ndim=1, flags='C_CONTIGUOUS')
]
lib.process_data.restype = None

class DataInput(BaseModel):
    values: List[float]

@app.post("/process")
async def process_data(data: DataInput):
    try:
        input_array = np.array(data.values, dtype=np.float64)
        output_array = np.zeros_like(input_array)
        lib.process_data(input_array, len(input_array), output_array)
        return {"result": output_array.tolist()}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.get("/")
async def root():
    return {"message": "Processor service is running"}
