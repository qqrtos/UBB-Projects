<template>
	<div id="app">

		<div v-for="product in productsToShow" :key="product.DisplayName">
			<div class="col-sm-4 col-md-3 product_block" style="padding-bottom: 4rem;" :data-code="code">

				<product-component :productModel="product" />

			</div>

		</div>
		<div class="col-xs-6 col-xs-offset-3 col-md-2 col-md-offset-5">
            <p style="text-align:center; font-size: 12px;">{{productsToShow.length}} of {{products.length}} products</p>
			<input style="font-size: 12px " type="button" v-if="showButton" id="ShowMore" value="SHOW MORE" @click="loadNextFourProducts()" />
		</div>
	</div>
</template>


<script>
  
    export default {
     
        data: function () {
            return {
                products: window.products,
                productsToShow: [],
            }
        },
        methods: {
            loadNextFourProducts() {
                if (this.products.length - this.productsToShow.length < 4)
                    for (var i = this.productsToShow.length; i < this.products.length; i++)
                        this.productsToShow.push(this.products[i]);
                else
                {
                    var index = this.productsToShow.length;
                    for (i = 0; i < 4; i++)
                    {
                        this.productsToShow.push(this.products[index]);
                        index++;
                    }
                }
                
            },
            loadProducts() {
                for (var i = 0; i < 8; i++)
                this.productsToShow.push(this.products[i]);
            }

        },
      
        computed: {
            showButton() {
                return this.productsToShow.length < this.products.length;
            },

        },

        mounted() {
            this.loadProducts();
        }


    }

</script>