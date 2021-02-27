<template>
    <div id="app">
        <div style="text-align:center; ">
            <a :href="product.link">
                <img :src="product.image" style="height:150px; width:150px">
            </a>
            <br>
            <a :href="product.link">
                {{product.displayName}}
            </a>
            <br />
            <div v-if="product.minPrice == product.maxPrice">
                <p>{{product.minPriceFormatted}}</p>
            </div>
            <div v-else>
                <p>{{product.minPriceFormatted}} - {{product.maxPriceFormatted}}</p>
            </div>
        </div>
    </div>
</template>

<script>

export default {
    props: ["productModel"],
    data() {
        return {
            product: this.productModel,
        }
        },

}
</script>